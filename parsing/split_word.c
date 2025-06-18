/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:48:55 by hrami             #+#    #+#             */
/*   Updated: 2025/06/18 15:54:18 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	is_spc(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] != ' ' && str[i])
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

t_toke	*new(char *str, t_type type, int flag)
{
	t_toke	*new_toke;

	new_toke = gc_malloc(sizeof(t_toke), 1);
	if (!new_toke)
		return (NULL);
	new_toke->str = ft_strdup(str);
	new_toke->type = type;
	new_toke->fd = -1;
	new_toke->space_after = flag;
	new_toke->next = NULL;
	return (new_toke);
}

void	add_node(t_toke **toke, char **str, int count)
{
	t_toke	*tmp;
	t_toke	*after;
	int		i;
	int		space;

	tmp = *toke;
	i = 0;
	while (tmp && i++ < count)
		tmp = tmp->next;
	if (!tmp || !str || !str[0])
		return ;
	after = tmp->next;
	space = tmp->space_after;
	tmp->str = ft_strdup(str[0]);
	tmp->space_after = 1;
	i = 1;
	while (str[i])
	{
		if (!str[i + 1])
			tmp->next = new(str[i], WORD, space);
		else
			tmp->next = new(str[i], WORD, 1);
		tmp = tmp->next;
		i++;
	}
	tmp->next = after;
}

void	skip_doll(t_toke **toke)
{
	t_toke	*tmp;
	t_toke	*prev;

	tmp = *toke;
	prev = NULL;
	while (tmp && tmp->next)
	{
		if (tmp->type == WORD && !tmp->space_after
			&& !ft_strcmp(tmp->str, "$")
			&& (tmp->next->type == DB_QT || tmp->next->type == SNL_QT))
		{
			if (!prev)
				*toke = tmp->next;
			else
				prev->next = tmp->next;
			tmp = tmp->next;
			continue ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ambiguous(t_toke **toke)
{
	t_toke	*tmp;

	tmp = *toke;
	while (tmp)
	{
		if (is_spc(tmp->str))
			tmp->is_spc = 1;
		else
			tmp->is_spc = 0;
		tmp = tmp->next;
	}
}

void	split_word(t_toke **toke)
{
	t_toke	*tmp;
	char	**split;
	int		i;

	tmp = *toke;
	i = 0;
	skip_doll(toke);
	ambiguous(toke);
	while (tmp)
	{
		if (tmp->type == WORD && is_spc(tmp->str))
		{
			split = ft_split(tmp->str, ' ');
			if (split)
			{
				add_node(toke, split, i);
				tmp = *toke;
				i = 0;
				continue ;
			}
		}
		tmp = tmp->next;
		i++;
	}
}
