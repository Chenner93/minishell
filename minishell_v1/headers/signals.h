/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:11:13 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/03/11 15:12:18 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

/** signals_utils_1.c */
void		set_sigact_struct(struct sigaction *sigact,
				void (*handler)(int));
void		sig_handler(int signo);

#endif