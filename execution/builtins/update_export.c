/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:56:32 by hrami             #+#    #+#             */
/*   Updated: 2025/06/19 16:49:21 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/mini_shell.h"

void	add_new(t_copy **env, char *join, t_export *export)
{
	if (export->append)
		add_back(env, new_node(ft_strdup(join), ft_strdup(export->value + 1)));
	else if (!export->egal)
		add_back(env, new_node(ft_strdup(export->key),
				ft_strdup(export->value)));
	else
		add_back(env, new_node(ft_strdup(join), ft_strdup(export->value)));
}

void	update_join_key(t_copy *cur, char *val, int append, int egal)
{
	char	*new_val;

	if (append)
	{
		new_val = ft_strjoin(cur->value, val + 1);
		cur->value = new_val;
	}
	else if (!egal && *val)
		cur->value = ft_strdup(val);
	else if (egal)
		cur->value = ft_strdup(val);
}

void	update_key_only(t_copy *cur, char *val, int append, int egal)
{
	char	*new_val;

	if (append)
	{
		cur->key = ft_strjoin(cur->key, "=");
		new_val = ft_strjoin(cur->value, val + 1);
		cur->value = new_val;
	}
	else if (!egal && *val)
		cur->value = ft_strdup(val);
	else if (egal)
	{
		cur->key = ft_strjoin(cur->key, "=");
		cur->value = ft_strdup(val);
	}
}

void	update_var(t_copy **env, t_export *export)
{
	t_copy	*cur;
	char	*join;

	cur = *env;
	join = ft_str_join(export->key, "=");
	if (!ft_strcmp(export->key, "_") || !ft_strcmp(export->key, "secret_pwd"))
		return ;
	while (cur)
	{
		if (!ft_strcmp(cur->key, join))
		{
			update_join_key(cur, export->value, export->append, export->egal);
			return ;
		}
		if (!ft_strcmp(cur->key, export->key))
		{
			update_key_only(cur, export->value, export->append, export->egal);
			return ;
		}
		cur = cur->next;
	}
	add_new(env, join, export);
}
