/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:26:58 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/04 10:50:15 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_exit_value;

char	*get_env_var_name(char *arg)
{
	char	*env_var_name;
	size_t	i;

	if (*(arg) == '?')
	{
		env_var_name = (char *) malloc(sizeof(char) * 2);
		if (env_var_name == NULL)
			return (NULL);
		*(env_var_name) = '?';
		*(env_var_name + 1) = '\0';
		return (env_var_name);
	}
	i = 0;
	while (ft_isalpha(*(arg + i)) == 1024)
		i++;
	env_var_name = (char *) malloc(sizeof(char) * (i + 1));
	if (env_var_name == NULL)
		return (NULL);
	ft_strlcpy(env_var_name, arg, i + 1);
	return (env_var_name);
}

void	increment_arg_iterator(char *arg,
							size_t *arg_iter)
{
	if (ft_isalpha(*(arg + (*arg_iter) + 1)) == 1024)
	{
		while (ft_isalpha(*(arg + (*arg_iter) + 1)) == 1024)
			(*arg_iter)++;
	}
}

static size_t	get_env_var_len(char ***env_vars,
								char *arg,
								size_t i)
{
	char	*env_var_name;
	char	*env_var;
	size_t	env_var_len;

	env_var = 0;
	if (ft_isalpha(*(arg + i)) == 1024)
	{
		env_var_name = get_env_var_name(arg + i);
		env_var = get_value_by_name(env_vars, env_var_name);
		env_var_len = ft_strlen(env_var);
		free(env_var_name);
		free(env_var);
	}
	else
	{
		env_var = ft_itoa(g_exit_value);
		env_var_len = ft_strlen(env_var);
		free(env_var);
	}
	return (env_var_len);
}

size_t	count_arg_len(char ***env_vars,
					char *arg)
{
	size_t	i;
	size_t	arg_len;

	i = 0;
	arg_len = 0;
	while (*(arg + i) != '\0')
	{
		if (*(arg + i) == '$' && is_valid_env_var(arg + i))
		{
			i++;
			arg_len += get_env_var_len(env_vars, arg, i) + 1;
			increment_arg_iterator(arg, &i);
			continue ;
		}
		i++;
		arg_len++;
	}
	return (arg_len);
}
