/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_hndl_wild.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:05:00 by hrami             #+#    #+#             */
/*   Updated: 2025/06/19 16:03:23 by hrami            ###   ########.fr       */
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

void	*gc_realloc(char **matching, size_t old_size, size_t size)
{
	char	**tmp;

	tmp = gc_malloc((sizeof(char *) * size), 1);
	if (matching)
	{
		ft_memcpy(tmp, matching, (old_size * sizeof(char *)));
	}
	return (tmp);
}

int	match_string(const char *file_name, const char *str)
{
	const char	*s;
	const char	*p;
	const char	*star;
	const char	*ss;

	s = file_name;
	p = str;
	star = NULL;
	ss = NULL;
	while (*s)
	{
		if (*p == '?' || *p == *s)
		{
			s++;
			p++;
		}
		else if (*p == '*')
		{
			star = p++;
			ss = s;
		}
		else if (star)
		{
			p = star + 1;
			s = ++ss;
		}
		else
			return (0);
	}
	while (*p == '*')
		p++;
	return (*p == '\0');
}

void	sort_string_array(char **arr, int size)
{
	int		i;
	int		j;
	char	*tmp;

	if (!arr || size <= 1)
		return ;
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
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
