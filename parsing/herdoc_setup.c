/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:05:01 by hrami             #+#    #+#             */
/*   Updated: 2025/06/21 23:39:30 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*get_key(char *str, t_copy *copy)
{
	t_copy	*tmp;
	char	*join;

	tmp = copy;
	join = ft_strjoin(str, "=");
	while (tmp && str)
	{
		if (ft_strcmp(tmp->key, join) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

char	*get_var(char *str, int *i, t_copy *copy, int checker)
{
	char	*to_search;
	char	*search;

	to_search = NULL;
	search = NULL;
	if (str && str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup(ft_itoa(checker)));
	}
	if (str && str[*i] == '$')
	{
		(*i)++;
		return (ft_strdup(""));
	}
	while (str && str[*i] && ft_isalnum(str[*i]))
	{
		to_search = ft_joinchar(to_search, str[*i]);
		(*i)++;
	}
	search = get_key(to_search, copy);
	return (search);
}

char	*expnand(char *str, t_copy *copy, int checker)
{
	char	*res;
	char	*join;
	int		i;

	res = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			join = get_var(str, &i, copy, checker);
			res = ft_strjoin(res, join);
		}
		else
		{
			res = ft_joinchar(res, str[i]);
			i++;
		}
	}
	return (res);
}

char	*expand_line(char *line, t_data *data)
{
	if (ft_strchr(line, '$'))
		line = expnand(line, data->copy_env, data->last_exit_status);
	return (line);
}
