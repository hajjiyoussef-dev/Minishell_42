/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_tacker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:44:55 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/03 23:03:05 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini_shell.h"


void add_fd(t_fd_track **head, int fd)
{
	t_fd_track *new;

	new = gc_malloc((sizeof(t_fd_track)), 1);
	new->fd = fd;
	new->next = *head;
	*head = new;
}


void close_all_fds(t_fd_track **head)
{
	t_fd_track *tmp;

	while (*head)
	{
		tmp = *head;
		if (tmp->fd > 2)
			close(tmp->fd);
		*head = (*head)->next;
	}
}
