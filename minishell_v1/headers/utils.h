/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:55:17 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/16 14:34:50 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/** utils_1.c */
void	skip_white_space_iterator_incr(char *raw,
			size_t *i);

void	skip_white_space_pointer_incr(char **raw);

/** split_minishell.c */
char	**split_minishell(char *str, char *charset);

#endif