/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:05:22 by yhajji            #+#    #+#             */
/*   Updated: 2025/05/02 23:26:08 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"


void handle_redirections(t_toke *cmd_start, t_toke *cmd_end)
{
	t_toke *curr = cmd_start;
	int fd;

	while (curr != cmd_end)
	{
		if (curr->type  = REDIR_OUT && curr->next)
		{
			fd = open(curr->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("open >  failed");
			}
		}
		
	}
	
}