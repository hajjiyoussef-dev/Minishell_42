/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:28:44 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/20 12:30:31 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/mini_shell.h"

int	help_atoi(const char *str, long long arr[], bool *overflow)
{
	if (str[arr[0]] < '0' || str[arr[0]] > '9')
		return (*overflow = true, 0);
	arr[3] = str[arr[0]] - '0';
	if ((arr[2] == 1 && (arr[1] > (LLONG_MAX - arr[3]) / 10)) || (arr[2] == -1
			&& (-arr[1] < (LLONG_MIN + arr[3]) / 10)))
		*overflow = true;
	if (*overflow)
		return (0);
	arr[1] = (arr[1] * 10) + arr[3];
	return (arr[1]);
}

long long	ft_atoi(const char *str, bool *overflow)
{
	long long	arr[4];

	*overflow = false;
	arr[0] = 0;
	arr[1] = 0;
	arr[2] = 1;
	while (str[arr[0]] == ' ' || str[arr[0]] == '\t' || str[arr[0]] == '\n'
		|| str[arr[0]] == '\v' || str[arr[0]] == '\f' || str[arr[0]] == '\r')
		arr[0]++;
	if (str[arr[0]] == '-' || str[arr[0]] == '+')
		if (str[arr[0]++] == '-')
			arr[2] = -1;
	if (!str[arr[0]])
		*overflow = true;
	while (str[arr[0]])
	{
		help_atoi(str, arr, overflow);
		arr[0]++;
	}
	if (*overflow)
		return (0);
	return (arr[1] * arr[2]);
}
