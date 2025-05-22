/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 01:47:13 by yhajji            #+#    #+#             */
/*   Updated: 2025/05/21 21:30:59 by yhajji           ###   ########.fr       */
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
		*error = 2;
		return (0);
	}
	arr[0] = (str[arr[2]] - 48) + (arr[0] * 10);
	return (arr[0]);
}

int	ft_atoi2(const char *str, bool *overflow)
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
		if (error == 2)
			*overflow = true;
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


int handle_exit(t_toke *tokns, t_toke *start)
{
	t_toke *curr = tokns;
	int exit_code = 0;
	bool overflow;

	overflow = false;
	while (curr && curr->next != NULL)
	{
		if (curr->type  == PIPE && (ft_strcmp(curr->next->str, "exit") == 0))
		{
			if (curr->next != NULL)
			{
				if (curr->next->next != NULL)
				{
					if (!ft_is_numeric(curr->next->next->str))
					{
						ft_putendl_fd("exit", STDERR_FILENO);
						ft_putstr_fd("bash: ", STDERR_FILENO);
						ft_putstr_fd(curr->next->str, STDERR_FILENO);
						ft_putendl_fd(": numeric argument required", STDERR_FILENO);
						return (2);
					}
					
				}
				if (curr->next->next)
				{
					exit_code = ft_atoi2(curr->next->next->str, &overflow);
					if (overflow == true)
					{
						ft_putendl_fd("exit", STDERR_FILENO);
						ft_putstr_fd("bash: exit: ", STDERR_FILENO);
						// ft_putstr_fd(curr->next->next->str, STDERR_FILENO);
						ft_putendl_fd(": numeric argument required", STDERR_FILENO);
						return (2);
					}
					return(exit_code);
				}
			}
			return (0);
		}
		curr = curr->next;
	}
	curr = start->next;
	if (!curr)
	{
		fprintf(stderr, "[debug] curr is NULL → exit\n");
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(0);
	}
	if (!ft_is_numeric(curr->str))
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("bash: exit: ", STDERR_FILENO);
		ft_putstr_fd(curr->str, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(2);
	}


	exit_code = ft_atoi2(curr->str, &overflow);
	if (overflow == true)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("bash: exit: ", STDERR_FILENO);
		ft_putstr_fd(curr->str, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(2);
	}	
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(exit_code % 256);
}
