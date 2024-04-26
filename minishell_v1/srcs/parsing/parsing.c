/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:03:44 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/09 09:23:21 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*get_cmd_name(char **cmd)
{
	char	*cmd_name;
	size_t	i;

	i = 0;
	while (cmd[i] != NULL && is_redirection_char(cmd[i][0]))
		i += 2;
	if (cmd[i] != NULL)
	{
		cmd_name = (char *) malloc(sizeof(char) * (ft_strlen(cmd[i]) + 1));
		if (cmd_name == NULL)
			return (NULL);
		ft_strlcpy(cmd_name, cmd[i], ft_strlen(cmd[i]) + 1);
		return (cmd_name);
	}
	return (NULL);
}

static void	on_allocation_failure(char ***cmds,
				t_cmd *cmds_lst,
				char ***env_vars)
{
	if (cmds != NULL)
		free_array_of_array((void ***) cmds);
	if (cmds_lst != NULL)
		free_cmds(cmds_lst);
	if (env_vars != NULL)
		free_array((void **)(*env_vars));
	exit(EXIT_FAILURE);
}

static t_cmd	*parse_cmd(char ***env_vars,
						char **cmd)
{
	t_cmd	*curr_node;
	char	*cmd_name;

	curr_node = cmd_init();
	if (curr_node == NULL || cmd == NULL || cmd[0] == NULL)
		return (NULL);
	cmd_name = get_cmd_name(cmd);
	if (cmd_name == NULL)
		return (NULL);
	set_cmd_is_buildin(curr_node, cmd_name);
	if (!set_cmd_path(env_vars, curr_node, cmd_name))
		return (free_cmds(curr_node), free(cmd_name), NULL);
	if (!set_cmd_args(env_vars, curr_node, cmd))
		return (free_cmds(curr_node), free(cmd_name), NULL);
	if (!set_cmd_redirection(env_vars, curr_node, cmd))
		return (free_cmds(curr_node), free(cmd_name), NULL);
	free(cmd_name);
	return (curr_node);
}

t_cmd	*parse_cmds(char ***env_vars,
				char *raw_input)
{
	t_cmd	*cmds_lst;
	t_cmd	*tmp_node;
	char	***cmds;
	size_t	i;

	cmds = NULL;
	cmds_lst = NULL;
	cmds = get_splitted_cmds(raw_input);
	if (cmds == NULL)
		return (on_allocation_failure(cmds, cmds_lst, env_vars), NULL);
	cmds_lst = parse_cmd(env_vars, cmds[0]);
	if (cmds_lst == NULL)
		return (on_allocation_failure(cmds, cmds_lst, env_vars), NULL);
	tmp_node = cmds_lst;
	i = 1;
	while (cmds[i] != NULL)
	{
		tmp_node->next = parse_cmd(env_vars, cmds[i]);
		if (tmp_node->next == NULL)
			return (on_allocation_failure(cmds, cmds_lst, env_vars), NULL);
		tmp_node = tmp_node->next;
		i++;
	}
	free_array_of_array((void ***) cmds);
	return (cmds_lst);
}
