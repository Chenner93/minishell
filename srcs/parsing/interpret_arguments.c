/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_arguments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:57:07 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/26 18:36:56 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_exit_value;

static char	*remove_quote(char *arg)
{
	size_t	arg_len;
	char	*result;

	arg_len = ft_strlen(arg);
	result = (char *) malloc(sizeof(char) * (arg_len - 1));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, arg + 1, arg_len - 1);
	return (result);
}

static bool	cpy_env_var_value_in_str(char ***env_vars,
								char **arg,
								char *res,
								size_t *res_iter)
{
	char	*env_var_name;
	char	*env_var_value;

	env_var_name = extract_env_var_name((*arg));
	if (env_var_name == NULL)
		return (false);
	if (*(env_var_name) == '?')
		env_var_value = ft_itoa(g_exit_value);
	else
		env_var_value = get_value_by_name(env_vars, env_var_name);
	(*arg) += ft_strlen(env_var_name) - 1;
	free(env_var_name);
	ft_strlcpy(res + (*res_iter), env_var_value, ft_strlen(env_var_value) + 1);
	(*res_iter) += ft_strlen(env_var_value) - 1;
	free(env_var_value);
	return (true);
}

char	*parse_arg(char ***env_vars,
					char *arg)
{
	char	*arg_iter;
	char	*res;
	size_t	res_iter;

	arg_iter = arg;
	res = allocate_result_ptr(env_vars, arg_iter);
	if (res == NULL)
		return (NULL);
	res_iter = 0;
	while (*(arg_iter) != '\0')
	{
		if (is_valid_env_var(arg_iter))
		{
			arg_iter++;
			if (!cpy_env_var_value_in_str(env_vars, &arg_iter, res, &res_iter))
				return (free(res), NULL);
		}
		else
			*(res + res_iter) = *(arg_iter);
		arg_iter++;
		res_iter++;
	}
	*(res + res_iter) = '\0';
	return (res);
}

// static bool	interpret_argument(char ***env_vars,
// 							char **cmd,
// 							size_t index)
// {
// 	char	*tmp_str;
// 	char	*new_arg;

// 	new_arg = NULL;
// 	if (*(*(cmd + index)) == '"')
// 	{
// 		tmp_str = remove_quote(*(cmd + index));
// 		if (tmp_str == NULL)
// 			return (false);
// 		new_arg = parse_arg(env_vars, tmp_str);
// 		free(tmp_str);
// 	}
// 	else if (*(*(cmd + index)) == '\'')
// 		new_arg = remove_quote(*(cmd + index));
// 	else
// 		new_arg = parse_arg(env_vars, *(cmd + index));
// 	if (new_arg != NULL)
// 	{
// 		free(*(cmd + index));
// 		*(cmd + index) = new_arg;
// 	}
// 	return (new_arg != NULL);
// }

// bool	interpret_arguments(char ***env_vars,
// 						char **cmd)
// {
// 	size_t	i;

// 	i = 0;
// 	while (*(cmd + i) != NULL)
// 	{
// 		if (is_cmd_file_redir(*(*(cmd + i))))
// 			i++;
// 		if (!interpret_argument(env_vars, cmd, i))
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }
