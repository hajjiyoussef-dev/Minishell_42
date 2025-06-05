/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 01:47:13 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/01 20:17:22 by yhajji           ###   ########.fr       */
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


int handle_exit(t_toke *tokns, t_toke *start, t_data *data)
{
	t_toke *curr = tokns;
	int exit_code = 0;
	bool overflow;
	bool flag = false;

	overflow = false;
	while (curr)
    {
        if (curr->type == PIPE)
            flag = true;
        curr = curr->next;
    }
	curr = start;
	if (flag == true)
	{
		while (curr && curr->next != NULL && curr->next->type != PIPE)
		{
			if ((ft_strcmp(curr->str, "exit") == 0) && curr->next->type != PIPE)
			{
				if (curr->next->next != NULL && curr->next->next->type != PIPE)
				{
					write(2, "bash: exit: too many arguments\n", 32);
					return (1);
				}
				if (curr->next != NULL && curr->next->type != PIPE)
				{
					exit_code = ft_atoi2(curr->next->str, &overflow);
					if (!ft_is_numeric(curr->next->str) || overflow == true)
					{
						write(2, "bash: ", 7);
						ft_putstr_fd(curr->next->str, STDERR_FILENO);
						write(2, ": numeric argument required\n", 29);
						return (2);
					}
					return(exit_code);
				}
				return (0);
			}
			curr = curr->next;
		}
		return (2);
	}
	else if (flag == false)
	{
		curr = start->next;
		if (!curr)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			gc_malloc(0, 0);
			exit(0);
		}
		if (curr->next != NULL)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			ft_putstr_fd("bash: exit: ", STDERR_FILENO);
			ft_putendl_fd("too many arguments", STDERR_FILENO);
			gc_malloc(0, 0);
			return (1);
		}
		if (!ft_is_numeric(curr->str))
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			ft_putstr_fd("bash: exit: ", STDERR_FILENO);
			ft_putstr_fd(curr->str, STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			gc_malloc(0, 0);
			exit(2);
		}
		exit_code = ft_atoi2(curr->str, &overflow);
		if (overflow == true)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			ft_putstr_fd("bash: exit: ", STDERR_FILENO);
			ft_putstr_fd(curr->str, STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			gc_malloc(0, 0);
			exit(2);
		}	
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		data->last_exit_status = (exit_code % 256);
		gc_malloc(0, 0);
		exit(exit_code % 256);
	}
	return (0);
}

