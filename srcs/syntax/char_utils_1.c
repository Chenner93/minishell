/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:12:04 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/24 14:20:17 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool	is_cmd_file_redir(int c)
{
	if (c == '>' || c == '<')
		return (true);
	return (false);
}

bool	is_cmd_separator(int c)
{
	if (c == '|' || c == '&')
		return (true);
	return (false);
}

bool	is_quote(int c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}

bool	incr_if_sep_or_redir(char *c, size_t *i)
{
	char	sep;

	if (is_cmd_separator(c[(*i)]) || is_cmd_file_redir(c[(*i)]))
	{
		sep = c[(*i)];
		while (c[(*i)] == sep)
			(*i)++;
		return (true);
	}
	return (false);
}
