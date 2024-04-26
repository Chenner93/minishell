/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:31:23 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/05 10:34:20 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	set_cmd_is_buildin(t_cmd *curr_node,
						char *cmd_name)
{
	char	*builtins[7];
	size_t	i;

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(builtins[i], cmd_name, ft_strlen(builtins[i])) == 0
			&& ft_isalpha(*(cmd_name + ft_strlen(builtins[i]))) == 0)
		{
			curr_node->is_builtin = true;
			break ;
		}
		i++;
	}
}

static bool	cpy_path_in_cmd_path(t_cmd *curr_node,
							char *cmd_name)
{
	size_t	cmd_name_l;

	cmd_name_l = ft_strlen(cmd_name);
	curr_node->cmd_path = (char *) malloc(sizeof(char) * (cmd_name_l + 1));
	if (curr_node->cmd_path == NULL)
		return (false);
	ft_strlcpy(curr_node->cmd_path, cmd_name, ft_strlen(cmd_name) + 1);
	return (true);
}

bool	set_cmd_path(char ***env_vars,
				t_cmd *curr_node,
				char *cmd_name)
{
	char	*path;

	if (curr_node->is_builtin == true)
		return (true);
	if (cmd_name_is_a_path(cmd_name))
	{
		if (!cpy_path_in_cmd_path(curr_node, cmd_name))
			return (false);
		return (true);
	}
	path = get_value_by_name(env_vars, "PATH");
	if (path == NULL)
		return (false);
	curr_node->cmd_path = get_cmd_path(cmd_name, ft_split(path, ':'));
	if (curr_node->cmd_path == NULL)
		return (free(path), false);
	if (curr_node->cmd_path != NULL && *(curr_node->cmd_path) == '\0')
	{
		free(curr_node->cmd_path);
		curr_node->cmd_path = NULL;
	}
	return (free(path), true);
}

bool	set_cmd_args(char ***env_vars,
				t_cmd *curr_node,
				char **cmd)
{
	size_t	args_count;
	size_t	i;
	size_t	j;

	args_count = count_cmd_args(cmd);
	curr_node->cmd = (char **) malloc(sizeof(char *) * (args_count + 1));
	if (curr_node->cmd == NULL)
		return (false);
	i = 0;
	j = 0;
	while (cmd[i] != NULL)
	{
		if (is_redirection_char(cmd[i][0]))
		{
			i += 2;
			continue ;
		}
		curr_node->cmd[j] = parse_argument(env_vars, cmd[i]);
		if (curr_node->cmd[j] == NULL)
			return (false);
		i++;
		j++;
	}
	curr_node->cmd[j] = NULL;
	return (true);
}

bool	set_cmd_redirection(char ***env_vars,
						t_cmd *curr_node,
						char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (is_redirection_char(cmd[i][0]))
		{
			if (!handle_redirection(env_vars, curr_node, cmd[i], cmd[i + 1]))
				return (false);
			i++;
		}
		i++;
	}
	return (true);
}
