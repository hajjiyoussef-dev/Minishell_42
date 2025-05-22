/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 01:34:01 by yhajji            #+#    #+#             */
/*   Updated: 2025/05/21 21:45:14 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/mini_shell.h"


bool is_op_n(char *str)
{
	int i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (false);
	i = 2;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

int handle_echo(t_toke *start)
{
	t_toke *curr;
	bool is_opten;
	
	curr = start;
	is_opten = false;
	
	// case of < 1 echo hello !!! 
	while (curr && (curr->type == REDIR_IN || curr->type == REDIR_OUT || curr->type == APPEND || curr->type == HEREDOC))
	{
		if (curr->next)
			curr = curr->next->next;
		// else
		// 	return (1); 
	}

	if (curr && ft_strcmp(curr->str, "echo") == 0)
		curr = curr->next;

	while (curr && is_op_n(curr->str))
	{
		is_opten = true;
		curr = curr->next;
	}
	
	while (curr  && curr->type != PIPE && curr->type != REDIR_OUT && curr->type != REDIR_IN && curr->type != HEREDOC && curr->type != APPEND)
	{
		ft_putstr_fd(curr->str, STDOUT_FILENO);
		curr = curr->next;
		if (curr  && curr->type != PIPE && curr->type != REDIR_OUT && curr->type != REDIR_IN && curr->type != HEREDOC && curr->type != APPEND )
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!is_opten)
		ft_putstr_fd("\n", 1);
	return (0);
}
