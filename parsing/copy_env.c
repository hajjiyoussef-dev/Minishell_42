/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:06:27 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/19 13:22:35 by hrami            ###   ########.fr       */
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

static t_copy	*add_default_env_vars(t_copy *copy)
{
	char	*pwd;
	char	*tmp;

	tmp = ft_strdup("/usr/local/sbin:/usr/local/bin:");
	tmp = ft_strjoin(tmp, ft_strdup("/usr/sbin:/usr/bin:/sbin:/bin"));
	pwd = getcwd(NULL, 0);
	add_back(&copy, new_node(ft_strdup("PWD="), ft_strdup(pwd)));
	add_back(&copy, new_node(ft_strdup("SHLVL="), ft_strdup("1")));
	add_back(&copy, new_node(ft_strdup("_="), ft_strdup("/usr/bin/env")));
	add_back(&copy, new_node(ft_strdup("PATH="), tmp));
	free(pwd);
	return (copy);
}

static t_copy	*copy_env_vars(char **envp)
{
	t_copy	*copy;
	char	*key;
	char	*value;
	int		i;
	int		j;

	copy = NULL;
	i = 0;
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
	return (copy);
}

t_copy	*copy_env(char **envp)
{
	t_copy	*copy;
	t_copy	*tmp;

	if (!envp || !envp[0])
		return (add_default_env_vars(NULL));
	copy = copy_env_vars(envp);
	if (!copy)
		return (NULL);
	tmp = copy;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD=") == 0)
		{
			add_back(&copy, new_node("secret_pwd=", tmp->value));
			break ;
		}
		tmp = tmp->next;
	}
	return (copy);
}
