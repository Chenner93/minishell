/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:30:44 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/03/28 21:48:51 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_cmd	*cmd_init(void)
{
	t_cmd	*new_cmd_node;

	new_cmd_node = (t_cmd *) malloc(sizeof(t_cmd));
	if (new_cmd_node == NULL)
		return (NULL);
	new_cmd_node->is_builtin = false;
	new_cmd_node->cmd_path = NULL;
	new_cmd_node->cmd = NULL;
	new_cmd_node->fd_in = -2;
	new_cmd_node->fd_out = -2;
	new_cmd_node->next = NULL;
	return (new_cmd_node);
}

void	free_cmds(t_cmd *cmds_lst)
{
	t_cmd	*tmp;
	size_t	i;

	while (cmds_lst != NULL)
	{
		i = 0;
		if (cmds_lst->cmd_path != NULL)
			free(cmds_lst->cmd_path);
		if (cmds_lst->cmd != NULL)
			free_array((void **) cmds_lst->cmd);
		tmp = cmds_lst->next;
		free(cmds_lst);
		cmds_lst = tmp;
	}
	unlink(HERE_DOC);
}
