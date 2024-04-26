/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   white_space_utils_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:12:35 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/24 13:40:23 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool	is_white_space(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}

void	reverse_skip_white_space_iterator_incr(char *raw,
									size_t *i)
{
	while (is_white_space(raw[*i]) && *i > 0)
		(*i)--;
}

void	skip_white_space_iterator_incr(char *raw,
									size_t *i)
{
	while (is_white_space(*(raw + (*i))))
		(*i)++;
}
