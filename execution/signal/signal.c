/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 06:00:15 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/21 23:42:03 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

volatile sig_atomic_t	g_sig = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	if (sig == SIGINT && (g_sig != 5656 && g_sig != 555 && g_sig != 222))
	{
		write(1, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = 42;
	}
	if (sig == SIGINT && g_sig == 222)
	{
		close(0);
		write(1, "^C", 2);
		g_sig = 111;
	}
	if (g_sig == 555)
		write(1, "\n", 1);
}

void	sigint_handler2(int sig)
{
	(void)sig;
	if (sig == SIGINT && (g_sig != 5656 && g_sig != 555 && g_sig != 222))
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGINT && g_sig == 222)
	{
		close(0);
		g_sig = 111;
	}
}

void	signal_setup(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_setup2(void)
{
	signal(SIGINT, sigint_handler2);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_setup_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
