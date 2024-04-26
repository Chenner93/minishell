/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:22:03 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/26 18:37:11 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/** split_minishell.c */
char	**split_minishell(char *str, char *charset);

/** remove_useless_parenthesis.c */
bool	remove_useless_parenthesis(char **original);

/** the_axe.c */
bool	the_axe(char *original,
			char **left,
			char **right,
			size_t index_sep);

/** cmd_path.c */
bool	set_path(char ***env_vars,
			t_ast_node *node);

/** interpret_arguments_utils.c */
bool	is_valid_env_var(char *str);

char	*extract_env_var_name(char *str);

bool	count_env_var_len(char ***env_vars,
			char **str,
			size_t *count);

ssize_t	count_arg(char ***env_vars,
			char *str);

char	*allocate_result_ptr(char ***env_vars,
			char *arg);

/** interpret_arguments.c */
char	*parse_arg(char ***env_vars,
			char *arg);

// bool	interpret_arguments(char ***env_vars,
			// char **cmd);

/** cmd_args.c */
char	**get_array_of_cmd_args(char **args);

#endif