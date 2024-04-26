/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_call.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:27:36 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/05 09:56:53 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool	export_builtin(char ***env_vars, char *arg)
{
	char	*name;
	char	*value;
	bool	return_value;

	name = parse_env_var_name(arg);
	if (name == NULL || *(name) == '\0')
		return (write(2, "Invalid syntax\n", 15), false);
	while (*(arg) != '=' && *(arg) != '\0')
		arg++;
	arg++;
	value = parse_env_var_value(arg);
	if (value == NULL)
		return (write(2, "Error allocating memory.\n", 25), false);
	if (env_var_exist(env_vars, name))
		return_value = modify_env_var_value(env_vars, name, value);
	else
		return_value = add_env_var(env_vars, name, value);
	free(name);
	free(value);
	return (return_value);
}

void	export_call(t_cmd *cmd_lst, char ***env_vars)
{
	char	*arg;
	size_t	i;

	if (cmd_lst == NULL || cmd_lst->cmd == NULL
		|| ft_get_array_length((void **) cmd_lst->cmd) < 2)
	{
		write(2, "Missing argument\n", 17);
		return ;
	}
	i = 1;
	while (cmd_lst->cmd[i] != NULL)
	{
		arg = cmd_lst->cmd[i];
		if (!export_builtin(env_vars, arg))
			write(2, "Une erreur qlq pars, force pour trouver mdr.\n", 45);
		i++;
	}
}
