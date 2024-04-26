/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:31:24 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/05 10:26:11 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

bool	env_var_exist(char ***env_vars,
					char *name)
{
	size_t	i;
	size_t	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while ((*env_vars)[i] != NULL)
	{
		if (ft_strlen((*env_vars)[i]) + 1 >= name_len)
		{
			if (ft_strncmp((*env_vars)[i], name, name_len) == 0
				&& (*env_vars)[i][name_len] == '=')
				return (true);
		}
		i++;
	}
	return (false);
}

char	*extract_env_var_value(char *raw_env_var)
{
	char	*value;
	size_t	i;
	size_t	y;

	i = 0;
	while (*(raw_env_var + i) != '=' && *(raw_env_var + i) != '\0')
		i++;
	y = i + 1;
	while (*(raw_env_var + i) != '\0')
		i++;
	i = i - y;
	value = (char *) malloc(sizeof(char) * (i + 1));
	if (value == NULL)
		return (NULL);
	ft_strlcpy(value, raw_env_var + y, i + 1);
	return (value);
}

char	*concat_name_value(char *name,
						char *value)
{
	char	*env_var;
	size_t	name_len;
	size_t	value_len;

	if (name == NULL || value == NULL || *(name) == '\0')
		return (NULL);
	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	env_var = (char *) malloc(sizeof(char) * (name_len + value_len + 2));
	if (env_var == NULL)
		return (NULL);
	ft_strlcpy(env_var, name, name_len + 1);
	ft_strlcpy(env_var + name_len, "=", 2);
	ft_strlcpy(env_var + name_len + 1, value, value_len + 1);
	return (env_var);
}
