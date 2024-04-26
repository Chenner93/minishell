/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:09:48 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/03/24 15:55:50 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

/**
 * This struct contain all informations about the current prompt.
 * user -> login of the current user.
 * host -> hostname of the machine.
 * curr_path -> current path of the shell.
 * prompt -> texte to display before new command.
*/
typedef struct s_prompt
{
	char	user[64];
	char	host[64];
	char	curr_path[512];
	char	prompt[640];
}	t_prompt;

/** prompt_utils_1.c */
void	init_prompt(t_prompt *prompt);
void	set_prompt(t_prompt *prompt);

#endif