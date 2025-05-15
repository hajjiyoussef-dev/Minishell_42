#include "mini_shell.h"

int handle_heredoc(t_toke *toke, int flag, t_data *data)
{
	int fd;
	int w_fd;
	static int iF;
	char *path;
	char *line;

	data->redirection_failed = 0;
	path = ft_strjoin(ft_strdup("/tmp/heredoc"), ft_itoa(iF++));
	w_fd = open(path, O_CREAT | O_TRUNC, 0644);
	if (w_fd < 0)
		return (printf("minishell : heredoc error\n"), data->redirection_failed == 1, -1);
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
		write(w_fd, line, ft_strlen(line));
		write(w_fd, "\n", 1);
		free(line);
	}
	close(w_fd);
	fd = open(path, O_RDONLY);
	unlink(path);
	// printf("%d\n", fd);
	return (fd);
}

void	handle_file(t_toke *toke, t_data *data)
{
	t_toke *tmp;
	int flag = 1;

	tmp = toke;
	data->redirection_failed = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			flag = 2;
		if (tmp->type == APPEND)
		{
			if (flag)
			{
				tmp->fd = open(tmp->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (tmp->fd < 0)
				{
					flag = 0;
					printf("minishell : %s Permission denied\n", tmp->next->str);
					data->redirection_failed = 1;
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
					printf("minishell : %s No such file or directory\n", tmp->next->str);
					data->redirection_failed = 1;
				}
			}
		}
		if (tmp->type == REDIR_OUT)
		{
			if (flag)
			{
				tmp->fd = open(tmp->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (tmp->fd < 0)
				{
					flag = 0;
					printf("minshell : %s Permission denied\n", tmp->next->str);
					data->redirection_failed = 1;
				}
			}
		}
		if (tmp->type == HEREDOC)
		{

			tmp->fd = handle_heredoc(tmp, flag, data);
		}
		tmp = tmp->next;
	}
}
