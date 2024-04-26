/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 01:33:32 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/26 16:29:38 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**init_env_vars(char **envp)
{
	char	**env_vars;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (envp[i] != NULL)
		i++;
	env_vars = (char **) malloc(sizeof(char *) * (i + 1));
	if (env_vars == NULL)
		return (write_err("Error allocating env_vars.\n"), NULL);
	while (j < i)
	{
		env_vars[j] = (char *) malloc(sizeof(char) * (ft_strlen(envp[j]) + 1));
		if (env_vars[j] == NULL)
			return (ft_free_array((void **) env_vars), NULL);
		ft_strlcpy(env_vars[j], envp[j], ft_strlen(envp[j]) + 1);
		j++;
	}
	env_vars[j] = NULL;
	return (env_vars);
}

// bool	add_env_var(char ***env_vars,
// 				char *name,
// 				char *value)
// {
// 	char	*new_env_var;
// 	size_t	curr_arr_len;

// 	new_env_var = concat_name_value(name, value);
// 	if (new_env_var == NULL)
// 		return (false);
// 	curr_arr_len = ft_get_array_length((void **)(*env_vars));
// 	(*env_vars) = (char **) ft_realloc_array((void **)(*env_vars),
// 			sizeof(char *) * curr_arr_len,
// 			sizeof(char *) * (curr_arr_len + 2));
// 	if ((*env_vars) == NULL)
// 		return (false);
// 	(*env_vars)[curr_arr_len] = new_env_var;
// 	(*env_vars)[curr_arr_len + 1] = NULL;
// 	return (true);
// }

// bool	modify_env_var_value(char ***env_vars,
// 						char *name,
// 						char *value)
// {
// 	char	*env_var;
// 	size_t	name_len;
// 	size_t	i;

// 	env_var = concat_name_value(name, value);
// 	if (env_var == NULL)
// 		return (false);
// 	name_len = ft_strlen(name);
// 	i = 0;
// 	while ((*env_vars)[i] != NULL)
// 	{
// 		if (ft_strncmp((*env_vars)[i], name, name_len) == 0)
// 		{
// 			free((*env_vars)[i]);
// 			(*env_vars)[i] = env_var;
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (true);
// }

// modifier cette fonctions pour quelle retourne un bool (malloc echoue ou non)
// et prend un pointeur vers une string en param pour le resultat.
char	*get_value_by_name(char ***env_vars,
						char *name)
{
	char	*value;
	size_t	i;
	size_t	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while ((*env_vars)[i] != NULL)
	{
		if (ft_strlen((*env_vars)[i]) + 1 >= name_len
			&& ft_strncmp((*env_vars)[i], name, name_len) == 0
			&& (*env_vars)[i][name_len] == '=')
		{
			value = extract_env_var_value((*env_vars)[i]);
			if (value == NULL)
				return (write_err("Error allocating memory.\n"), NULL);
			return (value);
		}
		i++;
	}
	return (NULL);
}

void	delete_env_var(char ***env_vars,
					char *name)
{
	(void) env_vars;
	(void) name;
	// coder ca lol.
}
