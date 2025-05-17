#include "mini_shell.h"

char	*expand_line(char *line, t_data *data)
{
	if (ft_strchr(line, '$'))
		line = expnand_it(line, data->copy_env, data->last_exit_status);
	return(line);
}


int handle_heredoc(t_toke *toke, int flag, t_data *data)
{
	int fd;
	int w_fd;
	static int iF;
	char *path;
	char *line;

	data->redirection_failed = 0;
	// while (!access(path, F_OK))
	path = ft_strjoin(ft_strdup("/tmp/heredoc"), ft_itoa(iF++));
	// falg dyal write lah n3al tabon mook rah fat7 file bla falg bash tktab fih zamal !!!!!!!!!!1!
	// (!)
	// ||
	// || // hak zob !!!
	// ||
   // ()()
	w_fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (w_fd < 0)
		return (printf("minishell : heredoc error\n"), data->redirection_failed = 1, -1);
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
		if (toke->next->type == WORD)
			line = expand_line(line, data);
		write(w_fd, line, ft_strlen(line));
		write(w_fd, "\n", 1);
		free(line);
	}
	close(w_fd);
	fd = open(path, O_RDONLY);
	unlink(path);
	return (fd);
}

void	handle_file(t_data *data)
{
	t_toke *tmp;
	int flag = 1;

	tmp = data->token;
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
			tmp->fd = handle_heredoc(tmp, flag, data);
		tmp = tmp->next;
	}
}
