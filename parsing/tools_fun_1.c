/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_fun_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:38:03 by hrami             #+#    #+#             */
/*   Updated: 2025/06/21 23:38:59 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_joinchar(char *s, char c)
{
	char	*ret;
	int		i;

	i = 0;
	ret = gc_malloc(ft_strlen(s) + 2, 1);
	if (!ret)
		return (NULL);
	while (s && s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = c;
	i++;
	ret[i] = '\0';
	return (ret);
}

char	*get_str(char *str, t_copy *copy)
{
	t_copy	*tmp;

	tmp = copy;
	while (tmp && str)
	{
		if (ft_strcmp(tmp->key, ft_str_join(str, "=")) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

static int	get_length(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len++;
	}
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = get_length(n);
	result = gc_malloc(len + 1, 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		n = -n;
	}
	while (n != 0)
	{
		result[len - 1] = (n % 10) + '0';
		len--;
		n /= 10;
	}
	return (result);
}
