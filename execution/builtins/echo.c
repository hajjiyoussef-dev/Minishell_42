/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 01:34:01 by yhajji            #+#    #+#             */
/*   Updated: 2025/05/11 08:09:08 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/mini_shell.h"


bool is_op_n(char *str)
{
	if (ft_strcmp(str, "-n") != 0)
		return (false);
	return (true);
}

int handle_echo(t_data *data)
{
	t_toke *curr;
	bool is_opten;
	
	curr = data->token->next;
	is_opten = false;
	
	while (curr && is_op_n(curr->str))
	{
		is_opten = true;
		curr = curr->next;
	}
	while (curr)
	{
		// printf("---%s---\n", curr->str);
		ft_putstr_fd(curr->str, STDOUT_FILENO);
		curr = curr->next;
		if (curr)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!is_opten)
		ft_putstr_fd("\n", 1);
	return (0);
}