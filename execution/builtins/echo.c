/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 01:34:01 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/21 23:43:09 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

bool	is_op_n(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (false);
	i = 2;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

static t_toke	*skip_redirections(t_toke *curr)
{
	while (curr && (curr->type == REDIR_IN || curr->type == REDIR_OUT
			|| curr->type == APPEND || curr->type == HEREDOC))
	{
		if (curr->next)
			curr = curr->next->next;
		else
			return (NULL);
	}
	return (curr);
}

static t_toke	*process_echo_options(t_toke *curr, bool *is_opten)
{
	*is_opten = false;
	if (curr && ft_strcmp(curr->str, "echo") == 0)
		curr = curr->next;
	while (curr)
	{
		if (curr->type == REDIR_IN || curr->type == REDIR_OUT
			|| curr->type == APPEND || curr->type == HEREDOC)
		{
			if (curr->next)
				curr = curr->next->next;
			else
				break ;
			continue ;
		}
		if (is_op_n(curr->str))
		{
			*is_opten = true;
			curr = curr->next;
		}
		else
			break ;
	}
	return (curr);
}

static void	print_echo_args(t_toke *curr, bool is_opten)
{
	bool	first_arg_printed;

	first_arg_printed = false;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == REDIR_OUT || curr->type == REDIR_IN
			|| curr->type == HEREDOC || curr->type == APPEND)
		{
			if (curr->next)
				curr = curr->next->next;
			else
				break ;
			continue ;
		}
		if (first_arg_printed)
			ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(curr->str, STDOUT_FILENO);
		first_arg_printed = true;
		curr = curr->next;
	}
	if (!is_opten)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

int	handle_echo(t_toke *start)
{
	t_toke	*curr;
	bool	is_opten;

	curr = skip_redirections(start);
	if (!curr)
		return (1);
	curr = process_echo_options(curr, &is_opten);
	print_echo_args(curr, is_opten);
	return (0);
}
