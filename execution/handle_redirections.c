/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:05:22 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/13 02:08:04 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini_shell.h"

int	get_the_redirections(t_toke *start)
{
	t_toke	*curr;

	curr = start;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == REDIR_IN || curr->type == HEREDOC)
		{
			if (curr->fd == -1)
				return (-1);
			dup2(curr->fd, STDIN_FILENO);
			close(curr->fd);
		}
		else if (curr->type == REDIR_OUT || curr->type == APPEND)
		{
			if (curr->fd == -1)
				return (-1);
			dup2(curr->fd, STDOUT_FILENO);
			close(curr->fd);
		}
		curr = curr->next;
	}
	return (0);
}
