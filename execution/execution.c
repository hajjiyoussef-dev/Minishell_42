/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:42:20 by yhajji            #+#    #+#             */
/*   Updated: 2025/05/16 22:35:44 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini_shell.h"

// for now !!!
char *ft_str_join3(char *s1, char *s2, char *s3)
{
    char *tmp = ft_str_join(s1, s2);
    char *result = ft_str_join(tmp, s3);
    return (result);
}

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
        joined = ft_str_join3(tmp->key, "=", tmp->value);
        // joined = ft_str_join(tmp->key, tmp->value);
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
		return (ft_str_dup2(argv));
	i = 0;
	while (ev[i] && ft_strnstr(ev[i], "PATH=", 5) == NULL)
		i++;
	if (!ev[i])
		return (NULL);
	paths = ft_sp_lit(ev[i] + 5, ':');
     
   // printf("sjdfkjdsbfjsdb\n");
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
    t_toke *prev = NULL;
    
    curr = cmd_start;
    while (curr && curr != end_cmd->next)
    {
        if (curr->type == WORD || curr->type == DB_QT || curr->type == SNL_QT)
            argc++;
        if (curr->type == REDIR_IN || curr->type == REDIR_OUT ||
            curr->type == APPEND || curr->type == HEREDOC)
            curr = curr->next; 
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
        if ((curr->type == WORD || curr->type == DB_QT || curr->type == SNL_QT ) )
        {
            if (!prev || (prev->type != REDIR_IN && prev->type != REDIR_OUT &&
                prev->type != APPEND && prev->type != HEREDOC))
            {
                argv[i] = ft_strdup(curr->str);
                if (!argv[i])
                {
                    perror("ft_strdup failed\n");
                    exit(1);
                }
                i++;
            }
        }
        if (curr->type == REDIR_OUT || curr->type == APPEND || curr->type == HEREDOC)
            curr = curr->next;
        // printf("hhhhh\n");
        prev = curr;
        if (curr)
            curr = curr->next;
    }
    argv[i] = NULL;
    return (argv);
}

bool is_cmd_buitin(char *argv)
{
    static char *buiti[] = {"env", "unset", "export", "pwd", "cd", "echo", "exit",  NULL};
    int i;

    i = 0;
    while (buiti[i] != NULL)
    {
         if (ft_strcmp(argv, buiti[i]) == 0)
            return (true);   
        i++;
    }
    return (false);
}

int execute_builtin(char **argv, t_data *data)
{
    if (ft_strcmp(argv[0], "env") == 0)
    {
        handle_env(data->token, data->copy_env);
        return (0);
    }
    else if (ft_strcmp(argv[0], "unset") == 0)
    {
        handle_unset(data->token, &data->copy_env);
        return (0);
    }
    else if (ft_strcmp(argv[0], "pwd") == 0)
    {
        return (handle_pwd(data)); 
    }
    else if (ft_strcmp(argv[0], "export") == 0)
    {
       return(handle_export(data));
    }
    else if (ft_strcmp(argv[0], "cd") == 0)
    {
        return (handle_cd(argv, data));
    }
    else if (ft_strcmp(argv[0], "echo") == 0)
    {
        return (handle_echo(data->token));
    }
    else if (ft_strcmp(argv[0], "exit") == 0)
    {
        return (handle_exit(data->token));
    }
    return (0);
}

int get_the_redirections(t_toke *start)
{
    t_toke *curr;
    
    curr = start;
    while (curr && curr->type != PIPE)
    {
        if (curr->type == REDIR_IN || curr->type == HEREDOC)
        {
            if (curr->fd == -1)
            {
                perror(curr->next->str);
                return (-1);   
            }
            dup2(curr->fd, STDIN_FILENO);
            close(curr->fd);
        }
        else if (curr->type == REDIR_OUT || curr->type == APPEND)
        {
            if (curr->fd == -1)
            {
                perror(curr->next->str);
                return (-1);
            }
            dup2(curr->fd, STDOUT_FILENO);
            close(curr->fd);
        }
        curr = curr->next;
    }
    return (0);
}


void execute_cmd(t_data *data, t_toke *start, t_toke *end)
{
    char **argv;
    char *cmd_path;
    pid_t pid;
    int status;
    
    signal_setup_child();
    if (get_the_redirections(start) < 0)
    {
        exit(1);
    }
//     if (data->redirection_failed)
//        exit(1);
    
    argv = build_argv(start, end);
    // for (int i = 0; argv[i]; i++)
    //     printf("{%s }the argv storge \n", argv[i]);
    if (!argv || !argv[0])
    {
        free_gc_malloc();
        return;
    }
    if (is_cmd_buitin(argv[0]))
    {
        data->last_exit_status = execute_builtin(argv, data);
        free(argv);
        return;
    }

    cmd_path = find_path(argv[0], env_list_to_array(data->copy_env));
    if (!cmd_path)
    {
        ft_putstr_fd("minibash: command not found: ", STDERR_FILENO);
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
        // free_gc_malloc();
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

int is_single_builtin_cmd(t_toke *start, t_toke *end)
{
    // Make sure there's no pipe in this segment
    t_toke *curr = start;
    while (curr && curr != end->next)
    {
        if (curr->type == PIPE)
            return 0;
        curr = curr->next;
    }
    // It is a single command — check if it's a builtin
    if (start && is_cmd_buitin(start->str) &&
        (ft_strcmp(start->str, "cd") == 0 ||
         ft_strcmp(start->str, "export") == 0 ||
         ft_strcmp(start->str, "unset") == 0 ||
         ft_strcmp(start->str, "exit") == 0))
        return 1;
    return 0;
}


void execute_cmds(t_data *data)
{
    t_toke *curr = data->token;
    t_toke *cmd_start;
    int p_fds[2];
    pid_t pid;
    int p_read_end_fd = -1;
    // char **argv;
    
    
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
            if (is_single_builtin_cmd(cmd_start, curr))
            {
                // data->last_exit_status = execute_builtin(&cmd_start->str, data);
                char **argv = build_argv(cmd_start, curr);
                data->last_exit_status = execute_builtin(argv, data);
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
