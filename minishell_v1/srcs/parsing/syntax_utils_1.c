/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckenaip <ckenaip@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:39:40 by maja              #+#    #+#             */
/*   Updated: 2024/04/16 09:31:51 by ckenaip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool	valid_quote_syntax(char *raw,
							size_t *i)
{
	char	quote_char;

	quote_char = *(raw + (*i));
	(*i)++;
	while (*(raw + (*i)) != quote_char && *(raw + (*i)) != '\0')
		(*i)++;
	if (*(raw + (*i)) == '\0')
		return (false);
	return (true);
}

static bool	valid_redirection_syntax(char *raw,
									size_t *i)
{
	if (*(raw + (*i)) == '<' || *(raw + (*i)) == '>')
	{
		(*i)++;
		if (*(raw + (*i)) == *(raw + (*i) - 1))
		{
			(*i)++;
			skip_white_space_iterator_incr(raw, i);
			return (!is_forbidden_char(*(raw + (*i))));
		}
		skip_white_space_iterator_incr(raw, i);
		return (!is_forbidden_char(*(raw + (*i))));
	}
	else if (*(raw + (*i)) == '|')
	{
		(*i)++;
		skip_white_space_iterator_incr(raw, i);
		return (!is_forbidden_char(*(raw + (*i))));
	}
	return (true);
}

bool	cmd_is_empty(char *raw_cmd)
{
	size_t	i;

	i = 0;
	while (*(raw_cmd + i) != '\0')
	{
		if (*(raw_cmd + i) > 32)
			return (false);
		i++;
	}
	return (true);
}

/**
 * 
*/
bool	check_valid_cmd_syntax(char *raw)
{
	size_t	i;

	i = 0;
	while (*(raw + i) != '\0')
	{
		if (*(raw + i) == '\'' || *(raw + i) == '"')
		{
			if (!valid_quote_syntax(raw, &i))
				return (false);
		}
		if (is_redirection_char(*(raw + i)))
		{
			if (!valid_redirection_syntax(raw, &i))
				return (false);
			continue ;
		}
		i++;
	}
	return (true);
}
