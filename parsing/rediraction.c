/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediraction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:55:19 by hrami             #+#    #+#             */
/*   Updated: 2025/06/18 16:11:03 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	handle_heredoc(t_toke *toke, t_data *data)
{
	int fd;
	int w_fd;
	static int Fh;
	char *path;
	char *tmp;
	char *line;
	int u;

	path = ft_strjoin(ft_strdup("/tmp/heredoc"), ft_itoa(Fh));
	while (!access(path, F_OK))
	{
		Fh++;
		path = ft_strjoin(ft_strdup("/tmp/heredoc"), ft_itoa(Fh));
	}
	w_fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (w_fd < 0)
		return (printf("minishell : heredoc error\n"), -1);
	g_sig = 222;
	while (1)
	{
		u = 0;
		line = NULL;
		line = readline("heredoc> ");
		if (g_sig == 111)
		{
			close(w_fd);
			unlink(path);
			return (-1337);
		}
		if (!line)
		{
			printf("minishell: warning: here-document at delimited by end-of-file (wanted `%s')\n", toke->next->str);
			break ;
		}
		if (!ft_strcmp(toke->next->str, line))
		{
			free(line);
			break ;
		}
		if (toke->next->type == WORD && ft_strchr(line, '$'))
		{
			tmp = expand_line(line, data);
			free(line);
			line = tmp;
			u = 1;
		}
		write(w_fd, line, ft_strlen(line));
		write(w_fd, "\n", 1);
		if (!u)
			free(line);
	}
	close(w_fd);
	fd = open(path, O_RDONLY);
	unlink(path);
	return (fd);
}

static void	handle_redir_in_out(t_toke *tmp, int *flag, t_data *data)
{
	int		mode;
	char	*msg;

	if (!*flag)
		return ;
	if ((!*tmp->next->str && tmp->next->type == WORD)
		|| (tmp->next->is_spc && tmp->next->type == WORD))
	{
		printf("minishell: ambiguous redirect\n");
		*flag = 0;
		return ;
	}
	mode = O_RDONLY;
	msg = "No such file or directory";
	if (tmp->type == REDIR_OUT)
	{
		mode = O_WRONLY | O_CREAT | O_TRUNC;
		msg = "Permission denied";
	}
	tmp->fd = open(tmp->next->str, mode, 0644);
	if (tmp->fd < 0)
	{
		*flag = 0;
		printf("minishell : %s %s\n", tmp->next->str, msg);
	}
	else
		add_fd(&data->fd_tracker, tmp->fd);
}

static void	handle_append(t_toke *tmp, int *flag, t_data *data)
{
	if (*flag)
	{
		if ((!*tmp->next->str && tmp->next->type == WORD)
			|| (tmp->next->is_spc && tmp->next->type == WORD))
		{
			printf("minishell: ambiguous redirect\n");
			*flag = 0;
			return ;
		}
		tmp->fd = open(tmp->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (tmp->fd < 0)
		{
			*flag = 0;
			printf("minishell : %s Permission denied\n", tmp->next->str);
		}
	}
	else
		add_fd(&data->fd_tracker, tmp->fd);
}

int	handle_file(t_data *data)
{
	t_toke	*tmp;
	int		flag;

	flag = 1;
	tmp = data->token;
	while (tmp)
	{
		if (tmp->type == PIPE)
			flag = 2;
		if (tmp->type == APPEND)
			handle_append(tmp, &flag, data);
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT)
			handle_redir_in_out(tmp, &flag, data);
		if (tmp->type == HEREDOC)
		{
			tmp->fd = handle_heredoc(tmp, data);
			if (tmp->fd == -1337)
			{
				data->last_exit_status = 130;
				return (-1337);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_her_doc(t_toke *toke)
{
	t_toke	*tmp;
	int		count;

	tmp = toke;
	count = 0;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			count += 1;
		tmp = tmp->next;
	}
	if (count > 16)
		return (1);
	return (0);
}
