/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:17:07 by hrami             #+#    #+#             */
/*   Updated: 2025/06/19 17:49:54 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/mini_shell.h"

static void	swap_env_nodes(t_copy *a, t_copy *b)
{
	char	*tmp_key;
	char	*tmp_val;

	tmp_key = a->key;
	tmp_val = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_val;
}

static void	sort_env(t_copy *env)
{
	t_copy	*cur;
	t_copy	*min;
	t_copy	*tmp;

	cur = env;
	while (cur)
	{
		min = cur;
		tmp = cur->next;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, min->key) < 0)
				min = tmp;
			tmp = tmp->next;
		}
		if (min != cur)
			swap_env_nodes(cur, min);
		cur = cur->next;
	}
}

void	print_export(t_data *data)
{
	t_copy	*cur;

	if (!data->copy_env)
		return ;
	sort_env(data->copy_env);
	cur = data->copy_env;
	while (cur)
	{
		if (ft_strcmp(cur->key, "_=") != 0)
		{
			if (!ft_strcmp(cur->key, "secret_pwd=") || (!ft_strcmp(cur->key, "PATH=") && data->is_env_i== true))
			{
				cur = cur->next;
				continue ;
			}
			if (ft_strchr(cur->key, '='))
				printf("declare -x %s\"%s\"\n", cur->key, cur->value);
			else
				printf("declare -x %s\n", cur->key);
		}
		cur = cur->next;
	}
}
