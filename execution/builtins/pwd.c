/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:16:24 by hrami             #+#    #+#             */
/*   Updated: 2025/06/21 23:42:21 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

int	help_pwd(t_copy *copy)
{
	t_copy	*tmp;

	tmp = copy;
	while (copy)
	{
		if (ft_strcmp(copy->key, "secret_pwd=") == 0)
		{
			printf("%s\n", copy->value);
			return (0);
		}
		copy = copy->next;
	}
	return (1);
}

int	handle_pwd(t_data *data)
{
	char	*pwd;
	char	*check;

	pwd = get_the_pathe(data->copy_env, "PWD=");
	if (pwd != NULL)
	{
		printf("%s\n", pwd);
		return (0);
	}
	else
	{
		check = getcwd(NULL, 0);
		if (check != NULL)
		{
			printf("%s\n", check);
			free(check);
			return (0);
		}
	}
	if (!help_pwd(data->copy_env))
		return (0);
	return (1);
}
