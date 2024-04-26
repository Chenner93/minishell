/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:42:04 by maja              #+#    #+#             */
/*   Updated: 2024/04/03 11:23:06 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

/** syntax_utils_1.c */
bool	check_valid_cmd_syntax(char *raw);

bool	cmd_is_empty(char *raw_cmd);

/** syntax_utils_2.c */

bool	is_white_space(int c);

bool	is_redirection_char(int c);

bool	is_forbidden_char(int c);

bool	is_valid_env_var(char *arg);

#endif