/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:39:40 by maja              #+#    #+#             */
/*   Updated: 2024/04/24 14:20:17 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool	valid_quote_syntax(char *raw,
							size_t *i)
{
	char	quote_char;

	quote_char = *(raw + (*i));
	(*i)++;
	while (*(raw + (*i)) != '\0')
	{
		if (*(raw + (*i)) == quote_char)
			break ;
		(*i)++;
	}
	if (*(raw + (*i)) == '\0')
		return (false);
	(*i)++;
	return (true);
}

static bool	valid_cmd_file_redirection(char *raw,
									size_t *i)
{
	(*i)++;
	if (*(raw + (*i) - 1) == *(raw + (*i)))
		(*i)++;
	skip_white_space_iterator_incr(raw, i);
	return (!is_cmd_file_redir(*(raw + (*i)))
		&& !is_cmd_separator(*(raw + (*i)))
		&& *(raw + (*i)) != '\0');
}

static bool	valid_cmd_separator_syntax(char *raw,
									size_t *i)
{
	(*i)++;
	if (*(raw + (*i) - 1) == '&' && *(raw + (*i)) != '&')
		return (false);
	if (*(raw + (*i) - 1) == '|' && *(raw + (*i)) == '|')
		(*i)++;
	else if (*(raw + (*i) - 1) == '&' && *(raw + (*i)) == '&')
		(*i)++;
	skip_white_space_iterator_incr(raw, i);
	return (!is_cmd_separator(*(raw + (*i)))
		&& *(raw + (*i)) != '\0');
}

bool	check_current_char(char *raw,
							size_t *i)
{
	if (is_quote(*(raw + (*i))))
	{
		if (!valid_quote_syntax(raw, i))
			return (false);
	}
	else if (is_cmd_file_redir(*(raw + (*i))))
	{
		if (!valid_cmd_file_redirection(raw, i))
			return (false);
	}
	else if (is_cmd_separator(*(raw + (*i))))
	{
		if (!valid_cmd_separator_syntax(raw, i))
			return (false);
	}
	else
		(*i)++;
	return (true);
}

bool	check_valid_cmd_syntax(char *raw)
{
	size_t	i;

	i = 0;
	skip_white_space_iterator_incr(raw, &i);
	if (is_cmd_separator(*(raw + i)))
		return (false);
	if (!valid_parenthesis_syntax(raw + i, 0))
		return (false);
	while (*(raw + i) != '\0')
	{
		if (!check_current_char(raw, &i))
			return (false);
	}
	return (true);
}
