/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediraction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:55:19 by hrami             #+#    #+#             */
/*   Updated: 2025/06/19 15:50:06 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	check_ambiguous_redirect(t_toke *tmp, int *flag)
{
	if ((!*tmp->next->str && tmp->next->type == WORD)
		|| (tmp->next->is_spc && tmp->next->type == WORD))
	{
		printf("minishell: ambiguous redirect\n");
		*flag = 0;
		return (1);
	}
	return (0);
}

static void	handle_redir_in_out(t_toke *tmp, int *flag, t_data *data)
{
	int		mode;
	char	*msg;

	if (!*flag || check_ambiguous_redirect(tmp, flag))
		return ;
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
