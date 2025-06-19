/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 01:28:56 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/19 15:45:42 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_toke	*replace_token(t_toke *head, t_toke *node_change, t_toke *new_tokne)
{
	t_toke	*prev;
	t_toke	*curr;
	t_toke	*tokne;

	prev = NULL;
	curr = head;
	tokne = new_tokne;
	while (curr && curr != node_change)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return (head);
	while (tokne && tokne->next != NULL)
		tokne = tokne->next;
	if (prev)
		prev->next = new_tokne;
	else
		head = new_tokne;
	if (tokne)
		tokne->next = curr->next;
	return (head);
}

char	**expand_wildcards(char *str, int *count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matching;
	int				size;

	size = 0;
	matching = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.' && str[0] != '.')
			continue ;
		if (match_string(entry->d_name, str))
		{
			matching = gc_realloc(matching, size, size + 2);
			matching[size++] = ft_strdup(entry->d_name);
			matching[size] = NULL;
		}
	}
	closedir(dir);
	*count = size;
	sort_string_array(matching, size);
	return (matching);
}

static int	replace_with_wildcards(t_toke **list, t_toke **curr)
{
	char	**matches;
	t_toke	*new_list;
	t_toke	*tmp;
	int		arr[2];

	arr[0] = 0;
	arr[1] = 0;
	matches = expand_wildcards((*curr)->str, &arr[0]);
	if (matches && arr[0] > 0)
	{
		new_list = NULL;
		while (arr[1] < arr[0])
		{
			add_token(&new_list,
				create_token(matches[arr[1]], WORD, 1));
			arr[1]++;
		}
		tmp = (*curr)->next;
		*list = replace_token(*list, *curr, new_list);
		*curr = tmp;
		return (1);
	}
	return (0);
}

void	handle_wildcards(t_toke **list)
{
	t_toke	*curr;

	curr = *list;
	while (curr)
	{
		if (curr->type == WORD && (ft_strchr(curr->str, '*')
				|| ft_strchr(curr->str, '?')))
		{
			if (replace_with_wildcards(list, &curr))
				continue ;
		}
		curr = curr->next;
	}
}
