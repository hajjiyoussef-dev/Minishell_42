/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 01:34:01 by yhajji            #+#    #+#             */
/*   Updated: 2025/05/16 22:26:37 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/mini_shell.h"


bool is_op_n(char *str)
{
	if (ft_strcmp(str, "-n") != 0)
		return (false);
	return (true);
}

int handle_echo(t_toke *start)
{
	t_toke *curr;
	bool is_opten;
	
	curr = start->next;
	is_opten = false;
	
	while (curr && is_op_n(curr->str))
	{
		is_opten = true;
		curr = curr->next;
	}
	while (curr && curr->type != PIPE)
	{
		// printf("---%s---\n", curr->str);
		ft_putstr_fd(curr->str, STDOUT_FILENO);
		curr = curr->next;
		if (curr && curr->type != PIPE)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!is_opten)
		ft_putstr_fd("\n", 1);
	return (0);
}