/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:11:13 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/24 11:37:42 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

/** signals_utils_1.c */
void		init_signals_structs(struct sigaction *sigact,
				struct termios *term,
				void (*handler)(int));\

void		sig_handler(int signo);

#endif