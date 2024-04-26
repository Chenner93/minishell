/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:13:36 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/24 11:42:19 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

extern int	g_exit_value;

static void	init_sigact_struct(struct sigaction *sigact,
							void (*handler) (int))
{
	ft_bzero(sigact, sizeof(*sigact));
	sigact->sa_handler = (__sighandler_t) handler;
	sigaction(SIGINT, sigact, NULL);
	sigaction(SIGQUIT, sigact, NULL);
}

static void	init_termios_struct(struct termios *term)
{
	tcgetattr(STDIN_FILENO, term);
	term->c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}

void	init_signals_structs(struct sigaction *sigact,
						struct termios *term,
						void (*handler)(int))
{
	init_sigact_struct(sigact, handler);
	init_termios_struct(term);
}

/**
 * Signals handler functions.
 * signo 2 -> CTRL + C
 * signo 3 -> CTRL + \
 * @param signo signal number.
 * @return void
*/
void	sig_handler(int signo)
{
	if (signo == 2)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_value = 130;
	}
	else if (signo == 3)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
