/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatinate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:32:19 by hrami             #+#    #+#             */
/*   Updated: 2025/06/21 23:40:15 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	help_concatinate(t_type type)
{
	if (type == WORD || type == DB_QT || type == SNL_QT)
		return (1);
	return (0);
}

t_toke	*concatinate(t_toke *head)
{
	t_toke	*tmp;
	t_toke	*nxt;

	tmp = head;
	while (tmp && tmp->next)
	{
		nxt = tmp->next;
		while (nxt && help_concatinate(nxt->type) && help_concatinate(tmp->type)
			&& !tmp->space_after)
		{
			tmp->str = ft_str_join(tmp->str, nxt->str);
			if (nxt && nxt->space_after)
			{
				nxt = nxt->next;
				break ;
			}
			nxt = nxt->next;
		}
		tmp->next = nxt;
		tmp = tmp->next;
	}
	return (head);
}
