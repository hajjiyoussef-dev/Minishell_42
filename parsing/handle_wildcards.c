/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 01:28:56 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/15 15:35:10 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"


char **expand_wildcards(char *str, int *count)
{
	DIR *dir;
	struct dirent *entry;
	char **matching;
	int size;

	size = 0;
	matching = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.' && str[0] != '.')
			continue;
		if (match_string(str, entry->d_name))
		{
			matching = gc_realloc(matching, (sizeof(char *) * size + 2));
			matching[size++] = ft_strdup(entry->d_name);
			matching[size] = NULL;
		}
	}
	closedir(dir);
	*count = size;
	return (matching);
}

void handle_wildcards(t_toke **list)
{
	t_toke *curr;
	t_toke *new_list;
	t_toke *tmp;
	int count;
	int i;
	char **matches;

	curr = *list;
	count = 0;
	i = 0;
	while (curr)
	{
		if (curr->type == WORD && (ft_strchr(curr->str, '*')))
		{
			matches = expand_wildcards(curr->str, &count);
			if (matches && count > 0)
			{
				new_list = NULL;
				while (i < count)
				{
					add_token(&new_list, create_token(matches[i], WORD, 1));
					i++;
				}
				tmp = curr->next;
				*list = replace_token(*list, curr, new_list);
				curr = tmp;
				continue;
			}
		}
		curr = curr->next;
	}
}
