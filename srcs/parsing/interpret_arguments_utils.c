/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_arguments_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:00:35 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/26 16:27:36 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_exit_value;

bool	is_valid_env_var(char *str)
{
	if (*(str) == '$' && !is_white_space(*(str + 1)) && *(str + 1) != '\0')
		return (true);
	return (false);
}

char	*extract_env_var_name(char *str)
{
	char	*result;
	size_t	i;

	i = 0;
	if (*(str) == '?')
		i = 1;
	else
	{
		while (*(str + i) != '\0' && !is_white_space(*(str + i)))
			i++;
	}
	result = (char *) malloc(sizeof(char) * (i + 1));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, str, i + 1);
	return (result);
}

bool	count_env_var_len(char ***env_vars,
						char **str,
						size_t *count)
{
	char	*env_var_name;
	char	*env_var_value;

	env_var_name = extract_env_var_name(*(str));
	if (env_var_name == NULL)
		return (false);
	if (*(*(str)) == '?')
	{
		env_var_value = ft_itoa(g_exit_value);
		if (env_var_value == NULL)
			return (false);
	}
	else
		env_var_value = get_value_by_name(env_vars, env_var_name);
	(*str) += ft_strlen(env_var_name) - 1;
	free(env_var_name);
	if (env_var_value == NULL)
		return (true); // ------
	(*count) += ft_strlen(env_var_value);
	free(env_var_value);
	return (true);
}

ssize_t	count_arg(char ***env_vars,
				char *str)
{
	size_t	count;

	count = 0;
	while (*(str) != '\0')
	{
		if (is_valid_env_var(str))
		{
			str++;
			if (!count_env_var_len(env_vars, &str, &count))
				return (-1);
		}
		else
			count++;
		str++;
	}
	return (count);
}

char	*allocate_result_ptr(char ***env_vars,
							char *arg)
{
	char	*result;
	ssize_t	result_count;

	result_count = count_arg(env_vars, arg);
	if (result_count == -1)
		return (NULL);
	result = (char *) malloc(sizeof(char) * (result_count + 1));
	if (result == NULL)
		return (NULL);
	return (result);
}
