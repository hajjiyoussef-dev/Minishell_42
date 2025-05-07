/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:42:20 by yhajji            #+#    #+#             */
/*   Updated: 2025/05/06 16:54:17 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"


char **env_list_to_array(t_copy *copy_envp)
{
    t_copy *tmp;
    int count;
    char **envp_array;
    int i;
    char *joined;

    tmp = copy_envp;
    i = 0;
    count = 0;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    envp_array = gc_malloc((sizeof(char *) * (count + 1)));
    if (!envp_array)
        return (free_gc_malloc(), NULL);
    tmp = copy_envp;
    while (i < count)
    {
        joined = ft_str_join(tmp->key, tmp->value);
        envp_array[i] = joined;
        // free(joined);
        tmp = tmp->next;
        i++;
    }
    envp_array[i] = NULL;
    return (envp_array); 
}

char	*ft_get_argv_path_help(char *cmd, char **paths)
{
	int		i;
	char	*part_path;
	char	*real_path;

	i = 0;
	while (paths[i])
	{
		part_path = ft_str_join(paths[i], "/");
		real_path = ft_str_join(part_path, cmd);
		free(part_path);
		if (access(real_path, X_OK) == 0)
		{
			i = 0;
			while (paths[i])
			{
				free(paths[i]);
				i++;
			}
			// free(paths);
			return (real_path);
		}
		free(real_path);
		i++;
	}
	return (NULL);
}

char *find_path(char *argv, char **ev)
{
    int		i;
	char	**paths;
	char	*result;

	if (ft_str_chr(argv, '/') && access(argv, X_OK) == 0)
		return (ft_strdup(argv));
	i = 0;
	while (ev[i] && ft_str_nstr(ev[i], "PATH=", 5) == NULL)
		i++;
	if (!ev[i])
		return (NULL);
	paths = ft_split(ev[i] + 5, ':');
	if (!paths)
	{
		// free(argv);
		perror("Error: in geting the pathe\n");
	}
	result = ft_get_argv_path_help(argv, paths);
	// if (!result)
	// 	ft_free(paths);
	return (result);
}


char **build_argv(t_toke *cmd_start, t_toke *end_cmd)
{
    int argc = 0;
    t_toke *curr;
    char **argv;
    int i = 0;
    
    curr = cmd_start;
    while ((curr != end_cmd->next) && curr != NULL)
    {
        if (curr->type == WORD || curr->type == DB_QT || curr->type == SNL_QT)
            argc++;
        curr = curr->next;
    }
    argv = malloc(sizeof(char *) *(argc + 1));
    // argv = gc_malloc((sizeof(char *) *(argc + 1)));
    if (!argv)
    {
        perror("malloc failed\n");
        free_gc_malloc();
        exit(1);
    }
    curr = cmd_start;
    while (curr != NULL && (curr != end_cmd->next))
    {
        if (curr->type == WORD || curr->type == DB_QT || curr->type == SNL_QT)
        {
            argv[i] = ft_strdup(curr->str);
            if (!argv[i])
            {
                perror("ft_strdup failed\n");
                exit(1);
            }
        }
        // printf("hhhhh\n");
        i++;
        curr = curr->next;
    }
    argv[i] = NULL;
    return (argv);
}

// bool is_cmd_buitin(char *argv)
// {
    
// }

void execute_cmd(t_data *data, t_toke *start, t_toke *end)
{
    char **argv;
    char *cmd_path;
    pid_t pid;
    int status;


    signal_setup_child();
    argv = build_argv(start, end);
    // printf("{%s} {%s}\n", start->str, end->str);
    // // for (int i = 0; argv && argv[i]; i++)
    // printf(" %s\n",argv[0]);
    if (!argv || !argv[0])
    {
        free_gc_malloc();
        return;
    }
    // if (is_cmd_buitin(argv[0]))
    // {
    //     data->last_exit_status = execute_builtin(argv, data);
    //     free(argv);
    //     return;
    // }

    cmd_path = find_path(argv[0], env_list_to_array(data->copy_env));
    if (!cmd_path)
    {
        ft_putstr_fd("minibash: command not found: \n", STDERR_FILENO);
        ft_putendl_fd(argv[0], STDERR_FILENO);
        data->last_exit_status = 127;
        free_gc_malloc();
        return;
    }
    pid = fork();
    if (pid == 0)
    {
        
        execve(cmd_path, argv, env_list_to_array(data->copy_env));
        perror("execve failed\n");
        free_gc_malloc();
        exit(1);
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        // if(WIFEXITED(status))
        // {
        //     data->last_exit_status = WEXITSTATUS(status); 
        // }
        // else if (WIFSIGNALED(status))
        // {
        //     data->last_exit_status = 128 ; //..
        // }
    }
    else 
    {
        perror("fork failed\n");
        data->last_exit_status = 1;
    }
    free(cmd_path);
    free(argv);
}


void execute_cmds(t_data *data)
{
    t_toke *curr = data->token;
    t_toke *cmd_start;
    int p_fds[2];
    pid_t pid;
    int p_read_end_fd = -1;
    

    cmd_start = curr;
   
    while (curr)
    {
        if (curr->type == PIPE || curr->next == NULL)
        {
        
            if (curr->type == PIPE && pipe(p_fds) == -1)
            {
                perror("pipe failed");
                return;
            }
            pid = fork();
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
                // printf("{%s} {%s}\n", curr->str ,cmd_start->str);
                exit(data->last_exit_status);
            }
            else if (pid < 0)
            {
                perror("fork failed");
            }
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
    while (waitpid(-1, NULL, 0) > 0);
    
    
}
