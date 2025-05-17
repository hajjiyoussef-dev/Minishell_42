/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 01:47:13 by yhajji            #+#    #+#             */
/*   Updated: 2025/05/16 23:27:40 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/mini_shell.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	help_atoi(long long arr[], const char *str, int *error)
{
	if (!ft_isdigit(str[arr[2]]))
	{
		*error = 1;
		return (0);
	}
	if ((arr[0] > (2147483647 / 10) || (arr[0] == 2147483647 / 10
				&& (str[arr[2]] - '0') > 7)) || (arr[1] == -1
			&& arr[0] == 2147483647 / 10 && (str[arr[2]] - '0') == 8))
	{
		*error = 1;
		return (0);
	}
	arr[0] = (str[arr[2]] - 48) + (arr[0] * 10);
	return (arr[0]);
}

int	ft_atoi2(const char *str)
{
	long long	arr[3];
	int			error;

	error = 0;
	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 0;
	while (str[arr[2]] == ' ' || str[arr[2]] == '\f' || str[arr[2]] == '\n'
		|| str[arr[2]] == '\r' || str[arr[2]] == '\v')
		arr[2]++;
	if (str[arr[2]] == '-' && ft_isdigit(str[arr[2] + 1]))
		arr[1] *= -1;
	if ((str[arr[2]] == '+' && ft_isdigit(str[arr[2] + 1]))
		|| (str[arr[2]] == '-' && ft_isdigit(str[arr[2] + 1])))
		arr[2]++;
	while (str[arr[2]])
	{
		arr[0] = help_atoi(arr, str, &error);
		if (error == 1)
			return (0);
		arr[2]++;
	}
	return (arr[0] * arr[1]);
}

bool	ft_is_numeric(const char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i]) 
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}


int handle_exit(t_toke *start)
{
	t_toke *curr;
	int exit_code = 0;

	curr = start->next;
	if (!curr || !start->prev || start->prev->type != PIPE)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	printf("jdjdjdjdjdjdjdj\n");
	if (!curr)
		exit(0);
	if (!ft_is_numeric(curr->str))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(curr->str, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(2);		
	}

	if (curr->next != NULL && curr->next->type != PIPE)
		return (1);
	exit_code = ft_atoi2(curr->str);
	exit(exit_code % 256);
}
