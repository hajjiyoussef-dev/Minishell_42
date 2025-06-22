/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 01:47:13 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/22 13:49:35 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

static void	exit_with_error(char *arg, int code, t_data *data)
{
	ft_putendl_fd("exit", 2);
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	close_all_fds(&data->fd_tracker);
	gc_malloc(0, 0);
	exit(code);
}

static bool	check_for_pipes(t_toke *tokns)
{
	t_toke	*curr;
	bool	has_pipe;

	curr = tokns;
	has_pipe = false;
	while (curr)
	{
		if (curr->type == PIPE)
			has_pipe = true;
		curr = curr->next;
	}
	return (has_pipe);
}

static int	handle_piped_exit(t_toke *start)
{
	t_toke	*curr;
	int		exit_code;
	bool	overflow;

	curr = start;
	while (curr && curr->next && curr->next->type != PIPE)
	{
		if (ft_strcmp(curr->str, "exit") == 0 && curr->next->type != PIPE)
		{
			if (curr->next->next && curr->next->next->type != PIPE)
				return (write(2, "bash: exit: too many arguments\n", 32), 1);
			if (curr->next && curr->next->type != PIPE)
			{
				exit_code = ft_atoi(curr->next->str, &overflow);
				if (overflow)
					return ((write(2, "bash: ", 7)
							, ft_putstr_fd(curr->next->str, 2))
						, write(2, ": numeric argument required\n", 29), 2);
				return (exit_code);
			}
			return (0);
		}
		curr = curr->next;
	}
	return (2);
}

static void	handle_standalone_exit(t_toke *curr, t_data *data)
{
	int		exit_code;
	bool	overflow;

	if (!curr)
	{
		ft_putstr_fd("exit\n", 1);
		(close_all_fds(&data->fd_tracker), gc_malloc(0, 0), exit(0));
	}
	if (curr->next)
	{
		ft_atoi(curr->str, &overflow);
		if (overflow)
			exit_with_error(curr->str, 2, data);
		ft_putendl_fd("exit", 2);
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		data->last_exit_status = 1;
		return ;
	}
	exit_code = ft_atoi(curr->str, &overflow);
	if (overflow)
		exit_with_error(curr->str, 2, data);
	ft_putstr_fd("exit\n", 1);
	data->last_exit_status = exit_code % 256;
	(close_all_fds(&data->fd_tracker), gc_malloc(0, 0), exit(exit_code % 256));
}

int	handle_exit(t_toke *tokns, t_toke *start, t_data *data)
{
	if (check_for_pipes(tokns))
		return (handle_piped_exit(start));
	else
	{
		handle_standalone_exit(start->next, data);
		return (data->last_exit_status);
	}
}
