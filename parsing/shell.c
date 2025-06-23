/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:16:51 by hrami             #+#    #+#             */
/*   Updated: 2025/06/23 15:30:13 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*ft_strrchr(const char *s, int c)
{
	const char		*last_one;
	unsigned char	c1;

	last_one = NULL;
	c1 = (unsigned char)c;
	while (*s != '\0')
	{
		if (*s == c1)
		{
			last_one = s;
		}
		s++;
	}
	if (c1 == '\0')
		return ((char *)s);
	return ((char *)last_one);
}

char *minishell_name(t_data *data)
{
	char *cmd;
	char *name;
	char *new_cmd;
	char *result;
	char *result_2;
	char *result_3;
	char *colored;

	cmd = getcwd(NULL, 0);
	if (!cmd)
	{
		cmd = get_the_pathe(data->copy_env, "PWD");
		if (!cmd)
			cmd = get_the_pathe(data->copy_env, "secret_pwd=");
		else 
			return (NULL);
	}
	name = ft_str_join(cmd, "$ ");
	if (!name)
		return (NULL);
	new_cmd = ft_strrchr(name, '/');
	if (!new_cmd)
		result = ft_strdup(name);  
	else
		result = ft_strdup(new_cmd + 1); 
	if (!result)
		return (NULL);
	colored = ft_strjoin("\033[1;34m", result);    
	result = ft_strjoin(colored, "\033[0m"); 
	if (data->last_exit_status == 0)
	{
		colored = ft_strjoin("\033[1;32m" , "->");
		result_2 = ft_strjoin(colored, "\033[0m ");
	}    
	else
	{
		colored = ft_strjoin("\033[31m" , "->");
		result_2 = ft_strjoin(colored, "\033[0m ");
	}
	result_3 = ft_strjoin(result_2, result);
	return (result_3);
}

static t_data	*init_data(char **envp)
{
	t_data	*data;

	if (!isatty(0) || !isatty(1))
		return (printf("please test the project in the right way\n"), NULL);
	data = gc_malloc(sizeof(t_data), 1);
	data->copy_env = copy_env(envp, data);
	signal_setup();
	return (data);
}

static int	process_tokens(t_data *data, t_toke *list, int org_in, char *line)
{
	if (data->last_exit_status == 0)
	{
		data->token = list;
		if (check_her_doc(list))
			exit((printf("minishell: maximum here-document count exceeded\n"),
					close_all_fds(&data->fd_tracker), gc_malloc(0, 0),
					free(line), 2));
		if (handle_file(data) == -1337)
			return (free(line), dup2(org_in, 0), close(org_in), 1);
		data->last_exit_status = execute_cmds(data);
	}
	return (0);
}

static int	read_and_prepare(t_data *data, char **line,
	t_toke **list, int org_in)
{
	char *name;
	
	name = minishell_name(data);
	// name = ft_str_join(name);
	*line = readline(name);
	if (g_sig == 42)
		data->last_exit_status = 130;
	if (!*line)
		return (printf("exit\n"), dup2(org_in, 0), -1);
	if ((*line)[0])
		add_history(*line);
	*list = lexer(*line);
	if (!(*line)[0])
		return (0);
	if (!(*list))
		data->last_exit_status = 2;
	expandd(*list, data->copy_env, data->last_exit_status);
	split_word(list);
	concatinate(*list);
	handle_wildcards(list);
	if (*list)
		data->last_exit_status = check_syntax(*list);
	return (0);
}

static void	minishell_loop(t_data *data)
{
	t_toke	*list;
	char	*line;
	int		org_in;

	printf("\033[2J\033[H");
	while (1)
	{
		signal_setup();
		org_in = dup(0);
		add_fd(&data->fd_tracker, org_in);
		g_sig = 1;
		if (read_and_prepare(data, &line, &list, org_in) == -1)
			break ;
		if (process_tokens(data, list, org_in, line))
			continue ;
		free(line);
		dup2(org_in, 0);
		close(org_in);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	int		exit_status;

	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	data = init_data(envp);
	if (!data)
		return (0);
	minishell_loop(data);
	exit_status = data->last_exit_status;
	close_all_fds(&data->fd_tracker);
	gc_malloc(0, 0);
	return (exit_status);
}
