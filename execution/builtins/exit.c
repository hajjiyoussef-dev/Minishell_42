/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 01:47:13 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/19 17:41:55 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/mini_shell.h"

long long	ft_atoi_ll(const char *str, bool *overflow)
{
	int				sign = 1;
	long long		result = 0;
	int				i = 0;
	int digit;

	*overflow = false;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	if (!str[i])
		*overflow = true;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (*overflow = true, 0);
		digit = str[i] - '0';
		if ((sign == 1 && (result > (LLONG_MAX - digit) / 10))
			|| (sign == -1 && (-result < (LLONG_MIN + digit) / 10)))
			*overflow = true;
		if (*overflow)
			return (0);
		result = result * 10 + digit;
		i++;
	}
	return (result * sign);
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
					exit_code = ft_atoi_ll(curr->next->str, &overflow);
					if (overflow == true)
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
			ft_atoi_ll(curr->next->str, &overflow);
			if (overflow == true)
			{
				ft_putendl_fd("exit", STDERR_FILENO);
				ft_putstr_fd("bash: exit: ", STDERR_FILENO);
				ft_putstr_fd(curr->str, STDERR_FILENO);
				ft_putendl_fd(": numeric argument required", STDERR_FILENO);
				gc_malloc(0, 0);
				exit(2);
			}
		}
		if (curr->next != NULL)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			ft_putstr_fd("bash: exit: ", STDERR_FILENO);
			ft_putendl_fd("too many arguments", STDERR_FILENO);
			return (1);
		}
		exit_code = ft_atoi_ll(curr->str, &overflow);
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
