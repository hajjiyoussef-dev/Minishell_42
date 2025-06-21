/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:16:51 by hrami             #+#    #+#             */
/*   Updated: 2025/06/21 22:58:25 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

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
	*line = readline("minishell> ");
	if (g_sig == 42)
		data->last_exit_status = 130;
	if (!*line)
		return (printf("exit\n"), dup2(org_in, 0), close(org_in), -1);
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
	gc_malloc(0, 0);
	return (exit_status);
}
