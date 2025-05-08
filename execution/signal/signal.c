/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 06:00:15 by yhajji            #+#    #+#             */
/*   Updated: 2025/05/07 20:37:06 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/mini_shell.h"

void sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void signal_setup_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
void signal_setup(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
