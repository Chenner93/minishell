/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:00:54 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/05 09:28:52 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# ifndef HERE_DOC
#  define HERE_DOC "/tmp/.here_doc_msh"
# endif

/** parsing.c */
t_cmd	*parse_cmds(char ***env_vars,
			char *raw_cmd);

/** parsing_utils_1.c */
void	set_cmd_is_buildin(t_cmd *curr_node,
			char *cmd_name);

bool	set_cmd_path(char ***env_vars,
			t_cmd *curr_node,
			char *cmd_name);

bool	set_cmd_args(char ***env_vars,
			t_cmd *curr_node,
			char **cmd);

bool	set_cmd_redirection(char ***env_vars,
			t_cmd *curr_node,
			char **cmd);

/** parsing_utils_2.c */
char	***get_splitted_cmds(char *raw_input);

bool	cmd_name_is_a_path(char *cmd_name);

int		check_cmd_path(char *path,
			char *cmd_name);

char	*get_cmd_path(char *cmd_name,
			char **paths);

size_t	count_cmd_args(char **cmd);

/** parsing_utils_3.c */

char	*parse_interpreted_argument(char ***env_vars,
			char *arg);

char	*parse_argument(char ***env_vars,
			char *arg);

/** parsing_utils_4.c */

size_t	count_arg_len(char ***env_vars,
			char *arg);

void	increment_arg_iterator(char *arg,
			size_t *arg_iter);

char	*get_env_var_name(char *arg);

/** parsing_utils_5.c */
bool	handle_redirection(char ***env_vars,
			t_cmd *curr_node,
			char *redir_type,
			char *redir_arg);

/** parsing_utils_6.c */
bool	write_here_doc(char ***env_vars,
			t_cmd *curr_node,
			char *delimiter);

#endif