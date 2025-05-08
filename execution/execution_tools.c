/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 04:35:06 by yhajji            #+#    #+#             */
/*   Updated: 2025/05/07 23:04:00 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini_shell.h"


char	*ft_str_chr(const char *s, int c)
{
	unsigned char	c1;

	c1 = (unsigned char)c;
	while (*s)
	{
		if (*s == c1)
		{
			return ((char *)s);
		}
		s++;
	}
	if (c1 == '\0')
		return ((char *)s);
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		while (needle[j] != '\0' && haystack[i + j] == needle[j] && (i
				+ j) < len)
		{
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
void ft_putstr_fd(char *str, int fd)
{
	int i = 0;

	while(str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

void ft_putendl_fd(char *str, int fd)
{
	int i = 0;

	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

