/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:28:34 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/19 20:20:14 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini_shell.h"

static int	count_valid_args(t_toke *cmd_start, t_toke *end_cmd)
{
	int		argc;
	t_toke	*curr;

	argc = 0;
	curr = cmd_start;
	while (curr && curr != end_cmd->next)
	{
		if (curr->type == WORD || curr->type == DB_QT || curr->type == SNL_QT)
			argc++;
		if (curr->type == REDIR_IN || curr->type == REDIR_OUT
			|| curr->type == APPEND || curr->type == HEREDOC)
			curr = curr->next;
		if (curr)
			curr = curr->next;
	}
	return (argc);
}

void	check(char **argv, int *i)
{
	if (!argv[*i])
	{
		ft_putendl_fd("ft_strdup failed: ", STDERR_FILENO);
		gc_malloc(0, 0);
		exit(1);
	}
}

static void	fill_argv_with_args(char **argv, t_toke *cmd_start, t_toke *end_cmd)
{
	t_toke	*curr;
	t_toke	*prev;
	int		i;

	i = 0;
	curr = cmd_start;
	prev = NULL;
	while (curr && curr != end_cmd->next)
	{
		if ((curr->type == WORD || curr->type == DB_QT || curr->type == SNL_QT)
			&& (!prev || (prev->type != REDIR_IN && prev->type != REDIR_OUT
					&& prev->type != APPEND && prev->type != HEREDOC)))
		{
			argv[i] = ft_strdup(curr->str);
			check(argv, &i);
			i++;
		}
		if (curr->type == REDIR_OUT || curr->type == APPEND
			|| curr->type == HEREDOC)
			curr = curr->next;
		prev = curr;
		if (curr)
			curr = curr->next;
	}
	argv[i] = NULL;
}

char	**build_argv(t_toke *cmd_start, t_toke *end_cmd, t_data *data)
{
	int		argc;
	char	**argv;

	(void)data;
	argc = count_valid_args(cmd_start, end_cmd);
	argv = gc_malloc(sizeof(char *) * (argc + 1), 1);
	if (!argv)
	{
		perror("gc_malloc failed\n");
		gc_malloc(0, 0);
		exit(1);
	}
	fill_argv_with_args(argv, cmd_start, end_cmd);
	return (argv);
}
