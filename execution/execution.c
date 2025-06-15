/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:42:20 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/15 15:36:13 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini_shell.h"

void execute_cmd(t_data *data, t_toke *start, t_toke *end)
{
    char **argv;
    char *cmd_path;
    pid_t pid;
    int status;
    int is_path_command;
    struct stat statbuf;
    
    signal_setup_child();
    if (get_the_redirections(start) < 0)
    {
        exit(1);
    }
    argv = build_argv(start, end, data);
    if (!argv || !argv[0])
    {
        return;
    }
    if (is_cmd_buitin(argv[0]))
    {
        data->last_exit_status = execute_builtin(argv, data, start);
        return;
    }
    is_path_command = (ft_strchr(argv[0], '/') != NULL);
    if (is_path_command) {
        cmd_path = argv[0];
    } else {
        cmd_path = find_path(argv[0], env_list_to_array(data->copy_env));
    }
    if (!cmd_path)
    {
        ft_putstr_fd(argv[0], STDERR_FILENO);
        ft_putendl_fd(": command not found ", STDERR_FILENO);
        data->last_exit_status = 127;
        return;
    }
    if (ft_strcmp(argv[0], "./minishell") == 0)
    {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        data->signal_status = 42;
    }
    pid = fork();
    g_sig = 5656;
    if (pid == 0)
    {
        signal_setup_child();
        if (stat(cmd_path, &statbuf) == 0)
        {
            if ((statbuf.st_mode & 0170000) == 0040000)
            {
                ft_putstr_fd("minishell: ", STDERR_FILENO);
                ft_putstr_fd(cmd_path, STDERR_FILENO);
                ft_putendl_fd(": Is a directory", STDERR_FILENO);
                exit(126);
            }
        }
        execve(cmd_path, argv, env_list_to_array(data->copy_env));
        if (errno == EACCES)
        {
            ft_putstr_fd("minishell: ", STDERR_FILENO);
            ft_putstr_fd(cmd_path, STDERR_FILENO);
            ft_putendl_fd(": Permission denied", STDERR_FILENO);
            exit(126);
        }
        else if (errno == ENOENT)
        {
            ft_putstr_fd("minishell: ", STDERR_FILENO);
            ft_putstr_fd(cmd_path, STDERR_FILENO);
            ft_putendl_fd(": No such file or directory", STDERR_FILENO);
            exit(127);
        }
        else if (errno == ENOEXEC)
        {
            char *sh_argv[] = {"/bin/sh", cmd_path, NULL};
            execve("/bin/sh", sh_argv, env_list_to_array(data->copy_env));
            perror("minishell: fallback with /bin/sh failed");
            exit(126);
        }
        else
        {
            perror("minishell");
        }
        gc_malloc(0, 0);
        exit(127);
    }
    else if (pid > 0)
    {
             
        waitpid(pid, &status, 0);
        if(WIFEXITED(status))
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
    else 
    {
        perror("fork failed");
        data->last_exit_status = 1;
    }
}

int     execute_cmds(t_data *data)
{
    t_toke *curr = data->token;
    t_toke *cmd_start;
    int p_fds[2];
    pid_t pid;
    pid_t last_pid = -1;
    int status;
    int p_read_end_fd = -1;
    pid_t waited_pid;
    t_toke *tmp = data->token;

    
    if (tmp && tmp->next == NULL && (ft_strcmp(tmp->str, "./minishell") == 0))
        signal_setup2();
    cmd_start = curr;
    while (curr)
    {
        if (curr->type == PIPE || curr->next == NULL)
        {
            if (curr->type == PIPE && pipe(p_fds) == -1)
            {
                perror("pipe failed");
                return (1);
            }
            if (is_single_builtin_cmd(data->token, curr) && curr->type != PIPE)
            {
                data->last_exit_status = execute_builtin(&cmd_start->str, data, cmd_start);
                return (data->last_exit_status);
            }
            pid = fork();
            g_sig = 555;
            if (pid == 0)
            {
                if (p_read_end_fd != -1)
                {
                    dup2(p_read_end_fd, STDIN_FILENO);
                    close(p_read_end_fd);
                }
                if (curr->type == PIPE)
                {
                    close(p_fds[0]);
                    dup2(p_fds[1], STDOUT_FILENO);
                    close(p_fds[1]);
                }
                execute_cmd(data, cmd_start, curr);                  
                int h = data->last_exit_status;
                close_all_fds(&data->fd_tracker);
                gc_malloc(0, 0);
                exit(h);
            }
            
            else if (pid < 0)
                perror("fork failed");
            else if (pid > 0)
                last_pid = pid;
            if (p_read_end_fd != -1)
                close(p_read_end_fd);
            if (curr->type == PIPE)
            {
                close(p_fds[1]);
                p_read_end_fd = p_fds[0];
            }
            cmd_start = curr->next;
        }
        curr = curr->next;
    }
    while ((waited_pid = waitpid(-1, &status, 0)) > 0)
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
    }
    close_all_fds(&data->fd_tracker);
    return (data->last_exit_status);
}
