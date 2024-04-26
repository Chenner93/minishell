/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parenthesis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckenaip <ckenaip@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 08:21:30 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/23 14:16:39 by ckenaip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool	check_specases_parenthesis(char *raw)
{
	size_t	i;

	i = 0;
	while (raw[i] && raw[i] != '(' && raw[i] != ')')
	{
		if (raw[i] == '\'' || raw[i] == '"')
			valid_quote_syntax(raw, &i);
		if (raw[i] != '\0')
			i++;
	}
	if (raw[i] == ')')
		return (false);
	while (raw[i])
	{
		if (raw[i] == '(')
		{
			i++;
			skip_white_space_iterator_incr(raw, &i);
			if (raw[i] == ')')
				return (false);
		}
		if (raw[i] != '\0')
			i++;
	}
	return (true);
}

static bool	check_open_parenthesis(char *raw, size_t pos)
{
	size_t		rev_pos;

	rev_pos = pos;
	if (rev_pos != 0)
		rev_pos--;
	reverse_skip_white_space_iterator_incr(raw, &rev_pos);
	if (!is_cmd_separator(raw[rev_pos]) && raw[rev_pos] != '(')
		return (false);
	pos++;
	skip_white_space_iterator_incr(raw, &pos);
	if (is_cmd_separator(raw[pos]))
		return (false);
	return (true);
}

static bool	check_close_parenthesis(char *raw, size_t pos)
{
	size_t		rev_pos;

	rev_pos = pos;
	if (rev_pos != 0)
		rev_pos--;
	reverse_skip_white_space_iterator_incr(raw, &rev_pos);
	if (is_cmd_separator(raw[rev_pos]))
		return (false);
	pos++;
	skip_white_space_iterator_incr(raw, &pos);
	if (!is_cmd_separator(raw[pos]) && raw[pos] != ')' && raw[pos])
		return (false);
	return (true);
}

bool	valid_parenthesis_syntax(char *raw, size_t i)
{
	int	count_par;

	count_par = 0;
	if (check_specases_parenthesis(raw) == false)
		return (false);
	while (raw[i])
	{
		if ((raw[i] == '\'' || raw[i] == '"')
			&& !valid_quote_syntax(raw, &i))
			return (false);
		else if (raw[i] == '(')
			count_par++;
		else if (raw[i] == ')')
			count_par--;
		if (count_par < 0
			|| (raw[i] == '(' && !check_open_parenthesis(raw, i))
			|| (raw[i] == ')' && !check_close_parenthesis(raw, i)))
			return (false);
		if (raw[i] != '\0')
			i++;
	}
	if (count_par == 0)
		return (true);
	return (false);
}
