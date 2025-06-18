/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:27:22 by hrami             #+#    #+#             */
/*   Updated: 2025/06/18 16:27:23 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	ft_free(char **arr, int i)
{
	while (i > 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}

static int	count_word(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

static char	*ft_str_dup(char const *str, int size)
{
	int		i;
	char	*arr;

	i = 0;
	arr = gc_malloc(size + 1, 1);
	if (!arr)
		return (NULL);
	while (str[i] && i < size)
	{
		arr[i] = str[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

static char	**extract_word(char const *s, char c, char **result)
{
	int	i;
	int	len;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		if (len > 0)
		{
			result[i] = ft_str_dup(s, len);
			if (result[i] == NULL)
			{
				ft_free(result, i);
				return (NULL);
			}
			i++;
		}
		s += len;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = gc_malloc((count_word(s, c) + 1) * sizeof(char *), 1);
	if (!result)
		return (NULL);
	return (extract_word(s, c, result));
}
