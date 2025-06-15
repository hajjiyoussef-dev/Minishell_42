/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 01:28:56 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/15 20:15:27 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"


void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (dest == src)
	{
		return (dest);
	}
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

void *gc_realloc(char **matching, size_t old_size, size_t size)
{
	char **tmp;
	
	tmp = gc_malloc((sizeof(char *) * size), 1);
	if (matching)
	{
		ft_memcpy(tmp, matching, (old_size * sizeof(char *)));
	}
	return (tmp);
}

t_toke *replace_token(t_toke *head, t_toke *node_change, t_toke *new_tokne)
{
	t_toke *prev;
	t_toke *curr;
	t_toke *tokne;

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


int match_string(const char *str, const char *file_name)
{
	if (*file_name == '\0' && *str == '\0')
		return (1);
	if (*file_name == '*')
	{
		if (match_string(str, file_name + 1))
			return (1);
		if (*str && match_string(str + 1, file_name))
			return (1);
		return (0);
	}
	if (*file_name == '?')
	{
		if (*str)
			return (match_string(str + 1, file_name + 1));
		else 
			return (0);
	}
	if (*file_name == *str)
		return (match_string(str + 1, file_name + 1));
	return (0);
}

void sort_string_array(char **arr, int size)
{
	int i, j;
	char *tmp;

	if (!arr || size <= 1)
		return;
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while(j < size - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

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
		if (curr->type == WORD && (ft_strchr(curr->str, '*') || ft_strchr(curr->str, '?')))
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
