/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_child_perror.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckenaip <ckenaip@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:04:36 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/05 10:57:23 by ckenaip          ###   ########.fr       */
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

static void	clean_up_fd(int **fd, int count_cmd)
{
	int	i;

	i = 0;
	while (i < count_cmd)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

void	clean_up_pipe(t_pipex *pipex, int in_child)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = pipex->first_node;
	if (in_child)
	{
		while (cmd != NULL)
		{
			tmp = cmd;
			cmd = cmd->next;
			clean_up_cmd(tmp);
		}
		free_array((void **)(*pipex->env_lst));
	}
	free(pipex->pid);
	clean_up_fd(pipex->fd, pipex->count_cmd);
	free(pipex);
}

void	exit_child_perror(t_pipex *pipex, char *message, int out)
{
	if (message != NULL)
		perror(message);
	clean_up_pipe(pipex, 1);
	exit(out);
}
