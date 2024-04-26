/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_axe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:06:44 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/23 14:28:06 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool	left_side(char *original,
				char **left,
				size_t index_sep)
{
	size_t	start;

	start = 0;
	skip_white_space_iterator_incr(original, &start);
	index_sep--;
	reverse_skip_white_space_iterator_incr(original, &index_sep);
	(*left) = (char *) malloc(sizeof(char) * (index_sep - start + 2));
	if ((*left) == NULL)
		return (false);
	ft_strlcpy((*left), original + start, index_sep - start + 2);
	return (true);
}

static bool	right_side(char *original,
					char **right,
					size_t index_sep)
{
	char	sep;
	size_t	end;

	sep = *(original + index_sep);
	while (*(original + index_sep) == sep)
		index_sep++;
	skip_white_space_iterator_incr(original, &index_sep);
	end = ft_strlen(original);
	end--;
	reverse_skip_white_space_iterator_incr(original, &end);
	(*right) = (char *) malloc(sizeof(char) * (end - index_sep + 2));
	if ((*right) == NULL)
		return (false);
	ft_strlcpy((*right), original + index_sep, end - index_sep + 2);
	return (true);
}

bool	the_axe(char *original,
			char **left,
			char **right,
			size_t index_sep)
{
	if (!left_side(original, left, index_sep)
		|| !right_side(original, right, index_sep))
		return (false);
	return (true);
}
