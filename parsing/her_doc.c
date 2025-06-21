/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:32:43 by hrami             #+#    #+#             */
/*   Updated: 2025/06/21 20:01:35 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	handle_heredoc_line(char **line, t_toke *toke,
	t_data *data, int w_fd)
{
	char	*tmp;
	int		expanded;

	if (!*line)
	{
		printf("minishell: warning:(wanted `%s')\n", toke->next->str);
		return (1);
	}
	if (!ft_strcmp(toke->next->str, *line))
		return (free(*line), 1);
	expanded = 0;
	if (toke->next->type == WORD && ft_strchr(*line, '$'))
	{
		tmp = expand_line(*line, data);
		free(*line);
		*line = tmp;
		expanded = 1;
	}
	write(w_fd, *line, ft_strlen(*line));
	write(w_fd, "\n", 1);
	if (!expanded)
		free(*line);
	return (0);
}

static int	write_heredoc_lines(int w_fd, char *path,
	t_toke *toke, t_data *data)
{
	char	*line;
	int		res;

	while (1)
	{
		line = readline("heredoc> ");
		if (g_sig == 111)
			return (close(w_fd), unlink(path), -1337);
		res = handle_heredoc_line(&line, toke, data, w_fd);
		if (res)
			break ;
	}
	return (0);
}

int	handle_heredoc(t_toke *toke, t_data *data)
{
	int			fd;
	int			w_fd;
	static int	fl;
	char		*path;

	path = ft_strjoin(ft_strdup("/tmp/heredoc"), ft_itoa(fl));
	while (!access(path, F_OK))
	{
		fl++;
		path = ft_strjoin(ft_strdup("/tmp/heredoc"), ft_itoa(fl));
	}
	w_fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (w_fd < 0)
		return (printf("minishell : heredoc error\n"), -1);
	g_sig = 222;
	if (write_heredoc_lines(w_fd, path, toke, data) == -1337)
		return (-1337);
	close(w_fd);
	fd = open(path, O_RDONLY);
	add_fd(&data->fd_tracker, fd);
	unlink(path);
	return (fd);
}

void	expand_heredoc(t_toke **tmp)
{
	t_toke	*prev;

	*tmp = (*tmp)->next;
	prev = *tmp;
	if (!*tmp)
		return ;
	if (!(*tmp)->next)
		return ;
	if (!ft_strcmp((*tmp)->str, "$"))
	{
		if (!(*tmp)->space_after && (*tmp)->next)
			(*tmp)->str = ft_strdup("");
		else
			(*tmp)->str = ft_strdup("$");
	}
	while (*tmp && !(*tmp)->space_after)
	{
		*tmp = (*tmp)->next;
		prev->type = DB_QT;
	}
}
