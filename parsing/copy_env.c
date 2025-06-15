/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:06:27 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/15 15:57:49 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_copy *new_node(char *key, char *value)
{
    t_copy *new;

    new = gc_malloc(sizeof(t_copy), 1);
    if (!new)
        return(NULL);
    new->key = key;
    new->value = value;
    new->next = NULL;
    return (new);
}

void add_back(t_copy **list, t_copy *new_copy)
{
	t_copy *tmp;

	if (*list == NULL)
    {
		*list = new_copy;
    }
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_copy;
	}
}

t_copy *copy_env(char **envp)
{

    int i = 0;
    int j;
    char    *key;
    char    *value;
    static char    *k[]= {"PWD=", "SHLVL=", "_=", NULL};
    static char    *v[] = {" ", "1", "/usr/bin/env", NULL};
    t_copy *copy = NULL;
    if (envp == NULL || envp[0] == NULL)
    {
        while (i < 3)
        {
            if (i == 0)
            {
                key = ft_strdup(k[i]);
                value = ft_strdup(getcwd(NULL, 0));
                add_back(&copy, new_node(key, value));
                i++;
            }
            key = ft_strdup(k[i]);
            value = ft_strdup(v[i]);
            add_back(&copy, new_node(key, value));
            i++;
        }
        add_back(&copy, new_node(ft_strdup("PATH="), ft_strdup("/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin")));
        return (copy);
    }
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
