/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:13:25 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/09 11:26:41 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	***get_splitted_cmds(char *raw_input)
{
	char	**tmp;
	char	***cmds;
	int		i;

	tmp = split_minishell(raw_input, "|");
	if (tmp == NULL)
		return (NULL);
	cmds = (char ***) malloc(sizeof(char **)
			* (ft_get_array_length((void **) tmp) + (sizeof(char **))));
	if (cmds == NULL)
		return (free_array((void **) tmp), NULL);
	i = 0;
	while (tmp[i] != NULL)
	{
		cmds[i] = split_minishell(tmp[i], "\t\v\n\f\r ");
		if (cmds[i] == NULL)
		{
			free_array_of_array((void ***) cmds);
			free_array((void **) tmp);
			return (NULL);
		}
		i++;
	}
	cmds[i] = NULL;
	return (free_array((void **)tmp), cmds);
}

bool	cmd_name_is_a_path(char *cmd_name)
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

static void	concat_path(char *res,
					char *curr_path,
					char *cmd_name)
{
	size_t	curr_path_len;
	size_t	cmd_name_len;

	curr_path_len = ft_strlen(curr_path);
	cmd_name_len = ft_strlen(cmd_name);
	ft_strlcpy(res, curr_path, curr_path_len + 1);
	ft_strlcpy(res + curr_path_len, "/", 2);
	ft_strlcpy(res + curr_path_len + 1, cmd_name, cmd_name_len + 1);
}

char	*get_cmd_path(char *cmd_name,
					char **paths)
{
	size_t	i;
	char	*path;

	i = 0;
	if (paths == NULL)
		return (NULL);
	while (paths[i] != NULL)
	{
		path = (char *) malloc(sizeof(char)
				* (ft_strlen(paths[i]) + ft_strlen(cmd_name) + 2));
		if (path == NULL)
			return (free_array((void *)paths), NULL);
		concat_path(path, paths[i], cmd_name);
		if (access(path, X_OK) == 0)
			return (free_array((void **) paths), path);
		free(path);
		i++;
	}
	free_array((void **) paths);
	path = (char *) malloc(sizeof(char) * 1);
	if (path == NULL)
		return (NULL);
	*(path) = '\0';
	return (path);
}

size_t	count_cmd_args(char **cmd)
{
	size_t	i;
	size_t	args_count;

	i = 0;
	args_count = 0;
	while (cmd[i] != NULL)
	{
		if (is_redirection_char(cmd[i][0]))
		{
			if (cmd[i + 1] == NULL)
				break ;
			i += 2;
			continue ;
		}
		i++;
		args_count++;
	}
	return (args_count);
}
