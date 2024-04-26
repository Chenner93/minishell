/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_useless_parenthesis.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:29:15 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/26 11:40:16 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool	suppress_parenthesis(char **original, size_t len_original)
{
	size_t	x;

	x = 1;
	while (*((*original) + x))
	{
		*((*original) + x - 1) = *((*original) + x);
		x++;
	}
	*((*original) + len_original - 1) = '\0';
	*((*original) + len_original - 2) = '\0';
	(*original) = (char *) ft_realloc((void *)(*original),
			sizeof(char) * len_original,
			sizeof(char) * (ft_strlen(*original) + 1));
	if ((*original) == NULL)
		return (false);
	x = 0;
	// printf("in suppres -----> %s\n", *original);
	skip_white_space_iterator_incr((*original), &x);
	if (*((*original + x)) == '(')
		remove_useless_parenthesis(original);
	return (true);
}

//take original and skip parenthesis
//take original and reverse skip parenthesis
//take both value and check it
static char	*skipped_white_space(char **original)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*new;

	start = 0;
	i = 0;
	end = ft_strlen(*original) - 1;
	skip_white_space_iterator_incr(*original, &start);
	reverse_skip_white_space_iterator_incr(*original, &end);
	new = malloc(sizeof(char) * (end - start + 2));
	if (new == NULL)
		return (NULL);
	while (start + i <= end)
	{
		new[i] = *(*(original) + start + i);
		i++;
	}
	new[i] = '\0';
	// printf("%s\n", new);
	free(*original);
	return (new);
}

bool	remove_useless_parenthesis(char **original)
{
	size_t	count;
	size_t	i;

	*original = skipped_white_space(original);
	count = 1;
	i = 0;
	if (*(*original + i) == '(')
	{
		i++;
		while (*(*(original) + i))
		{
			if (*(*(original) + i) == '(')
				count++;
			else if (*(*(original) + i) == ')')
				count--;
			if (count == 0)
				break ;
			i++;
		}
		if (i == ft_strlen(*original) - 1)
		{
			// printf("GOT THERE\n");
			if (!suppress_parenthesis(original, ft_strlen(*original)))
				return (false);
		}
	}
	return (true);
}
