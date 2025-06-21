/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 01:55:52 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/20 13:12:28 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/mini_shell.h"

void	handle_env(t_data *data)
{
	t_toke	*tmp;
	t_copy	*tmp_1;

	tmp = data->token;
	while (tmp)
	{
		if (!ft_strcmp("env", tmp->str))
		{
			tmp_1 = data->copy_env;
			while (tmp_1)
			{
				if (!ft_strcmp(tmp_1->key, "secret_pwd=")
					|| (!ft_strcmp(tmp_1->key, "PATH=")
						&& data->is_env_i == true))
				{
					tmp_1 = tmp_1->next;
					continue ;
				}
				if (ft_strchr(tmp_1->key, '='))
					printf("%s%s\n", tmp_1->key, tmp_1->value);
				tmp_1 = tmp_1->next;
			}
		}
		tmp = tmp->next;
	}
}
