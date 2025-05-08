#include "mini_shell.h"

int handle_heredoc(t_toke *toke, int flag)
{
	int fd;
	static int iF;
	char *path;
	char *line;

	path = ft_strjoin(ft_strdup("/tmp/heredoc"), ft_itoa(iF++));
	fd = open(path, O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (printf("minshell : heredoc error\n"), -1);
	while (1)
	{
		line = NULL;
		if (flag == 2)
			line = readline("PIPE heredoc> ");
		else
			line = readline("heredoc> ");
		if (!line || !ft_strcmp(toke->next->str, line))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	return (fd);
}

void	handle_file(t_toke *toke)
{
	t_toke *tmp;
	int flag = 1;

	tmp = toke;
	while (tmp)
	{
		if (tmp->type == PIPE)
			flag = 2;
		if (tmp->type == APPEND)
		{
			if (flag)
			{
				tmp->fd = open(tmp->next->str, O_RDONLY | O_CREAT | O_APPEND, 0644);
				if (tmp->fd < 0)
				{
					flag = 0;
					printf("minshell : %s Permission denied\n", tmp->next->str);
				}
			}
		}
		if (tmp->type == REDIR_IN)
		{
			if (flag)
			{
				tmp->fd = open(tmp->next->str, O_RDONLY);
				if (tmp->fd < 0)
				{
					flag = 0;
					printf("minshell : %s Permission denied\n", tmp->next->str);
				}
			}
		}
		if (tmp->type == REDIR_OUT)
		{
			if (flag)
			{
				tmp->fd = open(tmp->next->str, O_RDONLY | O_CREAT | O_TRUNC, 0644);
				if (tmp->fd < 0)
				{
					flag = 0;
					printf("minshell : %s Permission denied\n", tmp->next->str);
				}
			}
		}
		if (tmp->type == HEREDOC)
			tmp->fd = handle_heredoc(tmp, flag);
		tmp = tmp->next;
	}
}
