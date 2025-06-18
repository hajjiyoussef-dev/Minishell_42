/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:06:27 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/18 16:51:31 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_copy	*new_node(char *key, char *value)
{
	t_copy	*new;

	new = gc_malloc(sizeof(t_copy), 1);
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	add_back(t_copy **list, t_copy *new_copy)
{
	t_copy	*tmp;

	if (*list == NULL)
		*list = new_copy;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_copy;
	}
}

t_copy	*help_copy_env(t_copy *copy)
{
	char *pwd;
	
	pwd = getcwd(NULL, 0);
	add_back(&copy, new_node(ft_strdup("PWD="), ft_strdup(pwd)));;
	add_back(&copy, new_node(ft_strdup("SHLVL="), ft_strdup("1")));
	add_back(&copy, new_node(ft_strdup("_="), ft_strdup("/usr/bin/env")));
	add_back(&copy, new_node(ft_strdup("PATH="), ft_strdup("/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin")));
	free(pwd);
	return (copy);
}

t_copy	*copy_env(char **envp)
{

	int i = 0;
	int j;
	char    *key;
	char    *value;

	t_copy *copy = NULL;
	if (envp == NULL || envp[0] == NULL)
		return (help_copy_env(copy));
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		key = ft_substr(envp[i], 0, j + 1);
		if (!key)
		return (NULL);
		value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j);
		if (!value)
			return (NULL);
		add_back(&copy, new_node(key, value));
		i++;
	}
	t_copy *tmp = copy;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD=") == 0)
		{
			add_back(&copy, new_node("secret_pwd=", tmp->value));
		}
		tmp = tmp->next;
	}
	
	return (copy);
}
