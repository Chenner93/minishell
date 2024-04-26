/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:16:38 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/24 14:20:17 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

/** syntax.c */
bool	check_valid_cmd_syntax(char *raw);

bool	check_current_char(char *raw,
			size_t *i);
bool	valid_quote_syntax(char *raw,
			size_t *i);

/** syntax_utils_1.c */
bool	str_is_white_space(char *raw_cmd);

/** syntax_parenthesis.c */
bool	valid_parenthesis_syntax(char *raw, size_t i);

/** char_utils_1.c */
bool	is_cmd_file_redir(int c);

bool	is_cmd_separator(int c);

bool	is_quote(int c);

bool	incr_if_sep_or_redir(char *c, size_t *i);

/** white_space_utils_1.c */
bool	is_white_space(int c);

void	skip_white_space_iterator_incr(char *raw,
			size_t *i);

void	reverse_skip_white_space_iterator_incr(char *raw,
			size_t *i);

#endif