/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:42:20 by yhajji            #+#    #+#             */
/*   Updated: 2025/05/02 07:19:30 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	*ft_get_argv_path_help(char *cmd, char **paths)
{
	int		i;
	char	*part_path;
	char	*real_path;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		real_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(real_path, X_OK) == 0)
		{
			i = 0;
			while (paths[i])
			{
				free(paths[i]);
				i++;
			}
			free(paths);
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

	if (ft_strchr(argv, '/') && access(argv, X_OK) == 0)
		return (ft_strdup(argv));
	i = 0;
	while (ev[i] && ft_strnstr(ev[i], "PATH=", 5) == NULL)
		i++;
	if (!ev[i])
		return (NULL);
	paths = ft_split(ev[i] + 5, ':');
	if (!paths)
	{
		
		free(argv);
		perror("Error: in geting the pathe");
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
    while (curr != end_cmd && curr != NULL)
    {
        argc++;
        curr = curr->next;
    }
    
    argv = malloc(sizeof(char *) *(argc + 1));
    // argv = gc_malloc((sizeof(char *) *(argc + 1)));
    if (!argv)
    {
        perror("malloc failed");
        free_gc_malloc();
        exit(1);
    }
    curr = cmd_start;
    while (curr != NULL && curr != end_cmd)
    {
        argv[i] = ft_strdup(curr->str);
        // printf("hhhhh\n");
        if (!argv[i])
        {
            perror("ft_strdup failed");
            exit(1);
        }
        i++;
        curr = curr->next;
    }
    argv[i] = NULL;
    return (argv);
}


void execute_cmds(t_toke *tokens)
{
    t_toke *curr = tokens;
    t_toke *cmd_end ;
    t_toke *cmd_start;
    int p_fds[2];
    pid_t pid;
    int p_read_end_fd = -1;
    char **argv;
    t_data *cy_envp = NULL;
    

    cmd_start = tokens;
    printf("%s\n", curr->str);
    while (curr)
    {
        cmd_end = NULL;
        if (curr->type == PIPE)
        {
            cmd_end = curr;
        }
        else if (curr->next == NULL)
        {
            cmd_end = NULL;
        }
        if (cmd_end || curr->next == NULL)
        {
            if (curr->type == PIPE)
            {
                if (pipe(p_fds) == -1)
                {
                    perror("pipe failed");
                    exit(1);
                }
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
                argv = build_argv(cmd_start, cmd_end);
                printf("%s\n", argv[1]);
                execve(find_path(argv[0], cy_envp->envp), argv, NULL);
                perror("execve failed");
                free_gc_malloc();
                exit(1);
                
            }
            if (p_read_end_fd != -1)
                close(p_read_end_fd);
            if (curr->type == PIPE)
            {
                close(p_fds[1]);
                p_read_end_fd = p_fds[0];
            }
            if (curr->type == PIPE)
                curr = curr->next;
            
            cmd_start = curr; 
        }
        curr = curr->next;
    }
}
