/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:42:20 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/22 16:53:56 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	last_execution(t_data *data, char *cmd_path, char **argv)
{
	signal_setup_child();
	close_all_fds(&data->fd_tracker);
	check_if_directory(cmd_path);
	exec_ve_scope(data, cmd_path, argv);
	close_all_fds(&data->fd_tracker);
	gc_malloc(0, 0);
	exit(127);
}

int	check_argv_and_builtin(char **argv, t_data *data, t_toke *start)
{
	if (!argv || !argv[0])
		return (1);
	if (is_cmd_buitin(argv[0]))
	{
		data->last_exit_status = execute_builtin(argv, data, start);
		return (1);
	}
	return (0);
}

void	execute_cmd(t_data *data, t_toke *start, t_toke *end)
{
	char	**argv;
	char	*cmd_path;
	pid_t	pid;

	cmd_path = NULL;
	signal_setup_child();
	if (get_the_redirections(start) < 0)
		exit(1);
	argv = build_argv(start, end, data);
	if (check_argv_and_builtin(argv, data, start) == 1)
		return ;
	cmd_path = help_execute_cmd(data, cmd_path, argv);
	if (!cmd_path)
		return ;
	pid = fork();
	g_sig = 5656;
	if (pid == 0)
		last_execution(data, cmd_path, argv);
	else if (pid > 0)
		wait_all_child2(data, pid);
	else
		(perror("fork failed"), data->last_exit_status = 1);
}

pid_t	help_execute_cmds(t_data *data, t_toke *curr, t_toke *cmd_start,
		int *p_read_end_fd)
{
	int		p_fds[2];
	pid_t	arr[2];

	handle_pipe_creation(curr, p_fds);
	arr[0] = fork();
	g_sig = 555;
	if (arr[0] == 0)
	{
		pipe_duping(p_read_end_fd, curr, p_fds);
		call_execute_cmd(data, cmd_start, curr);
	}
	pipe_check(p_read_end_fd, arr, curr, p_fds);
	return (arr[1]);
}

int	execute_cmds(t_data *data)
{
	t_toke	*curr;
	t_toke	*cmd_start;
	pid_t	last_pid;
	int		p_read_end_fd;

	curr = data->token;
	check_minishell_special_case(data);
	cmd_start = curr;
	p_read_end_fd = -1;
	while (curr)
	{
		if (curr->type == PIPE || curr->next == NULL)
		{
			if (handle_builtin_no_pipe(data, cmd_start, curr))
				return (data->last_exit_status);
			last_pid = help_execute_cmds(data, curr, cmd_start, &p_read_end_fd);
			cmd_start = curr->next;
		}
		curr = curr->next;
	}
	wait_all_child(data, last_pid);
	close_all_fds(&data->fd_tracker);
	return (data->last_exit_status);
}
