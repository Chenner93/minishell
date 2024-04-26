/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:41:51 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/26 16:25:34 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool	cmd_name_is_a_path(char *cmd_name)
{
	size_t	i;

	i = 0;
	while (*(cmd_name + i) != '\0')
	{
		if (*(cmd_name + i) == '/')
			return (true);
		i++;
	}
	return (false);
}

static bool	concat_name_path(char **result,
						char *name,
						char *path)
{
	size_t	name_len;
	size_t	path_len;

	name_len = ft_strlen(name);
	path_len = ft_strlen(path);
	(*result) = (char *) malloc(sizeof(char) * (name_len + path_len + 2));
	if ((*result) == NULL)
		return (false);
	ft_strlcpy((*result), path, path_len + 1);
	ft_strlcpy((*result + path_len), "/", 2);
	ft_strlcpy((*result + path_len + 1), name, name_len + 1);
	return (true);
}

static bool	find_path(char **env_paths,
					char **result,
					char *cmd_name)
{
	size_t	i;

	i = 0;
	while (*(env_paths + i) != NULL)
	{
		if (!concat_name_path(result, cmd_name, *(env_paths + i)))
			return (false);
		if (access((*result), X_OK) == 0)
			return (true);
		free((*result));
		(*result) = NULL;
		i++;
	}
	return (true);
}

static bool	cpy_path(t_ast_node *node,
				char *path)
{
	size_t	path_len;

	path_len = ft_strlen(path);
	node->cmd_path = (char *) malloc(sizeof(char) * (path_len + 1));
	if (node->cmd_path == NULL)
		return (false);
	ft_strlcpy(node->cmd_path, path, path_len + 1);
	return (true);
}

bool	set_path(char ***env_vars,
			t_ast_node *node)
{
	char	*env_paths_str;
	char	**env_paths;
	char	*cmd_path;

	if (cmd_name_is_a_path(node->cmd[0]) && access(node->cmd[0], X_OK) == 0)
		return (cpy_path(node, node->cmd[0]));
	if (cmd_name_is_a_path(node->cmd[0]))
		return (true);
	env_paths_str = get_value_by_name(env_vars, "PATH");
	if (env_paths_str == NULL)
		return (false);
	env_paths = ft_split(env_paths_str, ':');
	free(env_paths_str);
	if (env_paths == NULL)
		return (false);
	if (!find_path(env_paths, &cmd_path, node->cmd[0]))
		return (ft_free_array((void *) env_paths), false);
	ft_free_array((void *) env_paths);
	if (cmd_path == NULL)
		return (true);
	node->cmd_path = cmd_path;
	return (true);
}
