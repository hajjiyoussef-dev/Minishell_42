/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_fun_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:41:12 by hrami             #+#    #+#             */
/*   Updated: 2025/06/18 15:44:16 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*ft_strdup(char *str)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i])
		i++;
	line = gc_malloc(i + 1, 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i])
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*sub;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	sub = gc_malloc(len + 1, 1);
	if (!sub)
		return (NULL);
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	new = gc_malloc(i + j + 1, 1);
	if (!new)
		return (NULL);
	j = 0;
	while (s1 && s1[j])
	{
		new[j] = s1[j];
		j++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		new[j + i] = s2[i];
		i++;
	}
	new[j + i] = '\0';
	return (new);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strchr(const char *str, int c)
{
	unsigned char	c1;
	int				i;

	c1 = (unsigned char)c;
	i = 0;
	while (str[i])
	{
		if (str[i] == c1)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
