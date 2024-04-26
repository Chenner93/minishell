/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 01:19:31 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/04 10:51:39 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env_var
{
	char				*name;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

/** env_utils_1.c */
char	**init_env_vars(char **envp);

bool	add_env_var(char ***env_vars,
			char *name,
			char *value);

bool	modify_env_var_value(char ***env_vars,
			char *name,
			char *value);

char	*get_value_by_name(char ***env_vars,
			char *name);

void	delete_env_var(char ***env_vars,
			char *name);

/** env_utils_2.c */

bool	env_var_exist(char ***env_vars,
			char *name);

char	*extract_env_var_value(char *raw_env_var);

char	*concat_name_value(char *name,
			char *value);

/** env_utils_3.c */

char	*parse_env_var_value(char *arg);

char	*parse_env_var_name(char *arg);

#endif
