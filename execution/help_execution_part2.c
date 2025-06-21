/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_execution_part2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:06:09 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/21 22:21:17 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini_shell.h"

void	pipe_check(int *p_read_end_fd, pid_t arr_pid[2], t_toke *curr,
		pid_t p_fds[2])
{
	if (arr_pid[0] < 0)
		perror("fork failed");
	else if (arr_pid[0] > 0)
		arr_pid[1] = arr_pid[0];
	if (*p_read_end_fd != -1)
		close(*p_read_end_fd);
	if (curr->type == PIPE)
	{
		close(p_fds[1]);
		*p_read_end_fd = p_fds[0];
	}
}

void	wait_all_child(t_data *data, pid_t last_pid)
{
	int		status;
	pid_t	waited_pid;

	waited_pid = waitpid(-1, &status, 0);
	while (waited_pid > 0)
	{
		if (waited_pid == last_pid)
		{
			if (WIFEXITED(status))
				data->last_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				data->last_exit_status = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGQUIT)
					write(1, "Quit\n", 5);
			}
		}
		waited_pid = waitpid(-1, &status, 0);
	}
}
