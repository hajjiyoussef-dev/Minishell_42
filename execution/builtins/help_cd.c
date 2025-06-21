/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:33:08 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/20 10:37:02 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/mini_shell.h"

void	print_getcwd_error(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": error retrieving current directory:", STDERR_FILENO);
	ft_putstr_fd(" getcwd: cannot access parent directories:", STDERR_FILENO);
	ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
}

void	update_env_value(t_copy *copy_env, char *str1, char *path)
{
	t_copy	*curr;

	curr = copy_env;
	while (curr)
	{
		if (ft_strcmp(curr->key, str1) == 0)
		{
			curr->value = ft_strdup(path);
			return ;
		}
		curr = curr->next;
	}
	add_back(&copy_env, new_node(ft_strdup(str1), ft_strdup(path)));
	while (curr)
	{
		if (!ft_strcmp(curr->key, "secret_pwd="))
		{
			curr->value = ft_strdup(path);
			return ;
		}
		curr = curr->next;
	}
	add_back(&copy_env, new_node(ft_strdup("secret_pwd="), ft_strdup(path)));
}

char	*get_the_pathe(t_copy *copy_env, char *str)
{
	t_copy	*curr;

	curr = copy_env;
	while (curr)
	{
		if (ft_strcmp(curr->key, str) == 0)
		{
			return (ft_strdup(curr->value));
		}
		curr = curr->next;
	}
	if (!ft_strcmp(str, "secret_pwd="))
	{
		while (curr)
		{
			if (ft_strcmp(curr->key, "secret_pwd=") == 0)
			{
				return (ft_strdup(curr->value));
			}
			curr = curr->next;
		}
	}
	return (NULL);
}
