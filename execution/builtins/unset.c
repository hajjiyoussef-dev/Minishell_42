/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:10:45 by hrami             #+#    #+#             */
/*   Updated: 2025/06/21 23:42:17 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

void	remove_var(t_copy **copy, char *key)
{
	t_copy	*cur;
	t_copy	*prev;
	char	*join;

	cur = *copy;
	prev = NULL;
	join = ft_strjoin(key, "=");
	while (cur)
	{
		if (!ft_strcmp(cur->key, key) || !ft_strcmp(cur->key, join))
		{
			if (!prev)
				*copy = cur->next;
			else
				prev->next = cur->next;
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
}

static void	handle_unset_args(t_toke **tmp, t_copy **copy)
{
	t_toke	*arg;

	arg = (*tmp)->next;
	while (arg && (arg->type == WORD
			|| arg->type == DB_QT || arg->type == SNL_QT))
	{
		if (!ft_strcmp(arg->str, "_") || !ft_strcmp(arg->str, "secret_pwd"))
		{
			arg = arg->next;
			continue ;
		}
		remove_var(copy, arg->str);
		arg = arg->next;
	}
	*tmp = arg;
}

int	handle_unset(t_toke *toke, t_copy **copy)
{
	t_toke	*tmp;

	tmp = toke;
	while (tmp)
	{
		if (!ft_strcmp("unset", tmp->str) && tmp->next)
		{
			handle_unset_args(&tmp, copy);
		}
		else
			tmp = tmp->next;
	}
	return (0);
}
