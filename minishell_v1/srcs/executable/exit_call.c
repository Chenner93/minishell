/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_call.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckenaip <ckenaip@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 09:16:53 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/05 14:57:21 by ckenaip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	clean_up_cmd(t_cmd *cmd_node)
{
	int	i;

	i = -1;
	while (cmd_node->cmd[++i])
		free(cmd_node->cmd[i]);
	free(cmd_node->cmd);
	free(cmd_node->cmd_path);
	free(cmd_node);
}

void	exit_call(t_pipex *pipex)
{
	t_cmd	*tmp;

	while (pipex->first_node)
	{
		tmp = pipex->first_node;
		pipex->first_node = pipex->first_node->next;
		clean_up_cmd(tmp);
	}
	free_array((void **)(*pipex->env_lst));
	clean_up_pipe(pipex, 0);
	exit(0);
}
