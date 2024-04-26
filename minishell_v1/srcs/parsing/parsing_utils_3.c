/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:14:15 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/03 11:13:44 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_exit_value;

static char	*parse_not_interpreted_argument(char *arg)
{
	char	*result;

	result = (char *) malloc(sizeof(char) * (ft_strlen(arg) - 1));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, (arg + 1), ft_strlen(arg) - 1);
	return (result);
}

static void	cpy_env_var_to_str(char ***env_vars,
								char *arg,
								char *result,
								size_t *result_iter)
{
	char	*env_var_name;
	char	*env_var;

	if (*(arg) == '?')
	{
		env_var = ft_itoa(g_exit_value);
		ft_strlcpy(result + (*result_iter), env_var, ft_strlen(env_var) + 1);
		(*result_iter) += ft_strlen(env_var) - 1;
		free(env_var);
		return ;
	}
	env_var_name = get_env_var_name(arg);
	if (env_var_name == NULL)
		return ;
	env_var = get_value_by_name(env_vars, env_var_name);
	ft_strlcpy(result + (*result_iter), env_var, ft_strlen(env_var) + 1);
	(*result_iter) += ft_strlen(env_var) - 1;
	free(env_var_name);
	free(env_var);
}

char	*parse_interpreted_argument(char ***env_vars,
								char *arg)
{
	char	*result;
	size_t	result_iter;
	size_t	arg_iter;

	result = (char *) malloc(sizeof(char) * (count_arg_len(env_vars, arg) + 1));
	if (result == NULL)
		return (NULL);
	result_iter = 0;
	arg_iter = 0;
	while (*(arg + arg_iter) != '\0')
	{
		if (*(arg + arg_iter) == '$' && is_valid_env_var(arg + arg_iter))
		{
			arg_iter++;
			cpy_env_var_to_str(env_vars, arg + arg_iter, result, &result_iter);
			increment_arg_iterator(arg, &arg_iter);
		}
		else
			*(result + result_iter) = *(arg + arg_iter);
		arg_iter++;
		result_iter++;
	}
	*(result + result_iter) = '\0';
	return (result);
}

char	*parse_argument(char ***env_vars,
					char *arg)
{
	if (*(arg) == '\'')
		return (parse_not_interpreted_argument(arg));
	if (*(arg) == '"')
	{
		*(arg + ft_strlen(arg) - 1) = '\0';
		return (parse_interpreted_argument(env_vars, arg + 1));
	}
	return (parse_interpreted_argument(env_vars, arg));
}
