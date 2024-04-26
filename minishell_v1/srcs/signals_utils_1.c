/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:13:36 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/03/11 14:58:24 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/**
 * Initialize the sigaction sigact struct.
 * The SIGINT & SIGQUIT signals are handled.
 * SIGINT -> CTRL + C
 * SIGQUIT -> CTRL + \
 * @param sigact* pointer to the sigaction struct to initialize.
 * @param handler* pointer to the signal handler function.
 * @return void
*/
void	set_sigact_struct(struct sigaction *sigact,
					void (*handler)(int))
{
	ft_bzero(sigact, sizeof(*sigact));
	sigact->sa_handler = (__sighandler_t) handler;
	sigaction(SIGINT, sigact, NULL);
	sigaction(SIGQUIT, sigact, NULL);
}

/**
 * Signals handler functions.
 * Function called when signals are received.
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
	}
	else if (signo == 3)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
