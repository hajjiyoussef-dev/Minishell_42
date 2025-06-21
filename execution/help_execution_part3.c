/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_execution_part3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:09:17 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/21 23:40:27 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	print_msg(char *arg, char *msg, int code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(code);
}

char	*help_execute_cmd(t_data *data, char *cmd_path, char **argv)
{
	bool	is_path;

	is_path = false;
	cmd_path = find_path(argv[0], env_list_to_array(data->copy_env), &is_path);
	if (!cmd_path)
	{
		ft_putstr_fd(argv[0], STDERR_FILENO);
		if (is_path)
			ft_putendl_fd(": command not found ", STDERR_FILENO);
		else
			perror(" ");
		data->last_exit_status = 127;
		return (NULL);
	}
	if ((ft_strcmp(argv[0], "./minishell") == 0) || (ft_strcmp(argv[0],
				"minishell") == 0))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	return (cmd_path);
}

void	exec_ve_scope(t_data *data, char *cmd_path, char **argv)
{
	char	*sh_argv[3];

	sh_argv[0] = "/bin/sh";
	sh_argv[1] = cmd_path;
	sh_argv[2] = NULL;
	execve(cmd_path, argv, env_list_to_array(data->copy_env));
	if (errno == EACCES)
	{
		print_msg(cmd_path, ": Permission denied", 126);
		exit(126);
	}
	else if (errno == ENOENT)
	{
		print_msg(cmd_path, ": No such file or directory", 127);
		exit(127);
	}
	else if (errno == ENOEXEC)
	{
		execve("/bin/sh", sh_argv, env_list_to_array(data->copy_env));
		perror("minishell: fallback with /bin/sh failed");
		exit(126);
	}
	else
		perror("minishell");
}

void	wait_all_child2(t_data *data, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		data->last_exit_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		data->last_exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit\n", 6);
	}
	close_all_fds(&data->fd_tracker);
}

void	check_if_directory(char *cmd_path)
{
	struct stat	statbuf;

	if (stat(cmd_path, &statbuf) == 0)
	{
		if ((statbuf.st_mode & 0170000) == 0040000)
		{
			print_msg(cmd_path, ": Is a directory", 126);
			exit(126);
		}
	}
}
