/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_split_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:02:21 by hrami             #+#    #+#             */
/*   Updated: 2025/06/22 18:23:19 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	help_skip_doll(t_toke *prev)
{
	if ((prev->type == REDIR_IN || prev->type == REDIR_OUT
			|| prev->type == APPEND || prev->type == HEREDOC))
		return (1);
	return (0);
}

void	skip_doll(t_toke **toke)
{
	t_toke	*tmp;
	t_toke	*prev;

	tmp = *toke;
	prev = NULL;
	while (tmp)
	{
		if (tmp->type == WORD && !*tmp->str)
		{
			if (prev && help_skip_doll(prev))
			{
				prev = tmp;
				tmp = tmp->next;
				continue ;
			}
			if (!prev)
				*toke = tmp->next;
			else
				prev->next = tmp->next;
			tmp = tmp->next;
			continue ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ambiguous(t_toke **toke)
{
	t_toke	*tmp;

	tmp = *toke;
	while (tmp)
	{
		if (is_spc(tmp->str))
			tmp->is_spc = 1;
		else
			tmp->is_spc = 0;
		tmp = tmp->next;
	}
}
