/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:48:55 by hrami             #+#    #+#             */
/*   Updated: 2025/06/21 23:39:13 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

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

static void	insert_words(t_toke *tmp, char **str, t_toke *after, int space)
{
	int	i;

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

void	add_node(t_toke **toke, char **str, int count)
{
	t_toke	*tmp;
	t_toke	*after;
	int		i;
	int		space;

	if (!toke || !str || !str[0])
		return ;
	tmp = *toke;
	i = 0;
	while (tmp && i++ < count)
		tmp = tmp->next;
	if (!tmp)
		return ;
	after = tmp->next;
	space = tmp->space_after;
	tmp->str = ft_strdup(str[0]);
	tmp->space_after = 1;
	insert_words(tmp, str, after, space);
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
