/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_priorities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:01:11 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/23 14:19:33 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	reverse_skip_quote(char *raw,
							size_t *i)
{
	char	quote;

	quote = *(raw + (*i));
	(*i)--;
	while (*(raw + (*i)) != '\0' && *(raw + (*i)) != quote)
		(*i)--;
}

static void	reverse_skip_parenthesis_incr(char *raw,
										size_t *i)
{
	size_t	count;

	count = 0;
	if (*(raw + (*i)) != ')')
		return ;
	while (1)
	{
		if (is_quote(*(raw + (*i))))
			reverse_skip_quote(raw, i);
		else if (*(raw + (*i)) == ')')
			count++;
		else if (*(raw + (*i)) == '(')
			count--;
		if (count == 0)
		{
			if ((*i) > 0)
				(*i)--;
			return ;
		}
		(*i)--;
	}
}

static ssize_t	find_prioritie(char *raw,
							size_t raw_len,
							char *prioritie)
{
	size_t	start;
	size_t	prioritie_len;

	start = 0;
	prioritie_len = ft_strlen(prioritie);
	while (raw_len > start)
	{
		if (*(raw + raw_len) == ')')
			reverse_skip_parenthesis_incr(raw, &raw_len);
		if (raw_len < prioritie_len)
			break ;
		if (ft_strncmp(raw + raw_len, prioritie, ft_strlen(prioritie)) == 0)
			return (raw_len);
		raw_len--;
	}
	return (-1);
}

size_t	get_highest_priorities(char *raw)
{
	ssize_t	result;
	size_t	raw_len;

	raw_len = ft_strlen(raw);
	result = find_prioritie(raw, raw_len - 1, "&&");
	if (result != -1)
		return (result);
	result = find_prioritie(raw, raw_len - 1, "||");
	if (result != -1)
		return (result);
	result = find_prioritie(raw, raw_len - 1, "|");
	if (result != -1)
		return (result);
	return (0);
}

t_type	get_prioritie_type(char *str,
						size_t index_sep)
{
	if (*(str + index_sep) == '&' && *(str + index_sep + 1) == '&')
		return (AND);
	if (*(str + index_sep) == '|' && *(str + index_sep + 1) == '|')
		return (OR);
	if (*(str + index_sep) == '|' && *(str + index_sep + 1) != '|')
		return (PIPE);
	return (-1);
}
