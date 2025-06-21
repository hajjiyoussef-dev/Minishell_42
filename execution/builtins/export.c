/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:18:00 by hrami             #+#    #+#             */
/*   Updated: 2025/06/20 13:11:45 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/mini_shell.h"

static int	is_valid_start(char *str, t_data *data)
{
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		data->last_exit_status = 1;
		return (0);
	}
	return (1);
}

static int	check_key(char *str, t_data *data, int *j)
{
	while (str[*j] && str[*j] != '=')
	{
		if (str[*j] == '+' && str[*j + 1] == '=')
			break ;
		if (!ft_isalnum(str[*j]) && str[*j] != '_')
		{
			printf("minishell: export: `%s': not a valid identifier\n", str);
			data->last_exit_status = 1;
			return (0);
		}
		(*j)++;
	}
	return (1);
}

static void	assign_flags(char *str, int j, t_export *export)
{
	export->append = 0;
	export->egal = 0;
	if (str[j] == '+' && str[j + 1] == '=')
		export->append = 1;
	else if (str[j] == '=')
		export->egal = 1;
}

static int	process_export_arg(t_data *data, t_toke **tmp)
{
	int			j;
	t_export	*export;

	j = 0;
	export = gc_malloc(sizeof(t_export), 1);
	if (!is_valid_start((*tmp)->next->str, data))
		return ((*tmp)->next = (*tmp)->next->next, 0);
	if (!check_key((*tmp)->next->str, data, &j))
		return ((*tmp)->next = (*tmp)->next->next, 0);
	assign_flags((*tmp)->next->str, j, export);
	export->key = ft_substr((*tmp)->next->str, 0, j);
	if (!export->key)
		return (1);
	if (!ft_strcmp(export->key, "PATH"))
		data->is_env_i = false;
	export->value = ft_substr((*tmp)->next->str, j + 1,
			ft_strlen((*tmp)->next->str) - j);
	if (!export->value)
		return (1);
	update_var(&data->copy_env, export);
	data->last_exit_status = 0;
	(*tmp)->next = (*tmp)->next->next;
	return (0);
}

int	handle_export(t_data *data)
{
	t_toke	*tmp;
	int		k;

	tmp = data->token;
	k = 0;
	while (tmp)
	{
		if (!ft_strcmp("export", tmp->str))
		{
			while (tmp->next && (tmp->next->type == WORD
					|| tmp->next->type == DB_QT || tmp->next->type == SNL_QT))
			{
				k++;
				process_export_arg(data, &tmp);
			}
			if (!k)
				print_export(data);
		}
		tmp = tmp->next;
	}
	return (data->last_exit_status);
}
