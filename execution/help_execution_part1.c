/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_execution_part1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:01:03 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/21 23:40:42 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	check_minishell_special_case(t_data *data)
{
	t_toke	*tmp;

	tmp = data->token;
	if (tmp && tmp->next == NULL
		&& (ft_strcmp(tmp->str, "./minishell") == 0
			|| ft_strcmp(tmp->str, "minishell") == 0))
	{
		signal_setup2();
	}
}

int	handle_pipe_creation(t_toke *curr, int p_fds[2])
{
	if (curr->type == PIPE && pipe(p_fds) == -1)
	{
		perror("pipe failed");
		return (-1);
	}
	return (0);
}

int	handle_builtin_no_pipe(t_data *data, t_toke *cmd_start, t_toke *curr)
{
	if (is_single_builtin_cmd(data->token, curr) && curr->type != PIPE)
	{
		data->last_exit_status = execute_builtin(&cmd_start->str, data,
				cmd_start);
		return (1);
	}
	return (0);
}

void	pipe_duping(int *p_read_end_fd, t_toke *curr, int p_fds[2])
{
	if (*p_read_end_fd != -1)
	{
		dup2(*p_read_end_fd, STDIN_FILENO);
		close(*p_read_end_fd);
	}
	if (curr->type == PIPE)
	{
		close(p_fds[0]);
		dup2(p_fds[1], STDOUT_FILENO);
		close(p_fds[1]);
	}
}

void	call_execute_cmd(t_data *data, t_toke *cmd_start, t_toke *curr)
{
	int	h;

	h = 0;
	execute_cmd(data, cmd_start, curr);
	h = data->last_exit_status;
	close_all_fds(&data->fd_tracker);
	gc_malloc(0, 0);
	exit(h);
}
