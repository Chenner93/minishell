/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckenaip <ckenaip@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:52:14 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/02 14:45:08 by ckenaip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	count_cmd(t_pipex *pipex)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = pipex->first_node;
	while (cmd != NULL)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

void	error_free_fd(int **fd, int count_cmd)
{
	int	i;

	if (fd == NULL)
		return ;
	i = -1;
	while (++i < count_cmd)
		free(fd[i]);
	free(fd);
}

static int	**init_fd(int count_cmd)
{
	int	**fd;

	fd = malloc(sizeof(int *) * count_cmd);
	if (fd == NULL)
		return (NULL);
	int (i) = -1;
	while (++i < count_cmd)
		fd[i] = NULL;
	i = 0;
	while (i < count_cmd)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (fd[i] == NULL)
			return (error_free_fd(fd, count_cmd), NULL);
		fd[i][0] = -1;
		fd[i][1] = -1;
		i++;
	}
	return (fd);
}

static void	init_pid(int *pid, int count_cmd)
{
	int	i;

	i = 0;
	while (i < count_cmd)
	{
		pid[i] = -1;
		i++;
	}
}

t_pipex	*init_cmd_pipe(t_cmd *cmd_lst, char ***env_lst)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (pipex == NULL)
		return (NULL);
	pipex->first_node = cmd_lst;
	pipex->cmd_lst = cmd_lst;
	pipex->fd_in = cmd_lst->fd_in;
	pipex->fd_out = cmd_lst->fd_out;
	pipex->count_cmd = count_cmd(pipex);
	pipex->fd = init_fd(pipex->count_cmd);
	pipex->pid = malloc(sizeof(int) * pipex->count_cmd);
	pipex->env_lst = env_lst;
	if (pipex->fd == NULL || pipex->pid == NULL)
	{
		error_free_fd(pipex->fd, pipex->count_cmd);
		free(pipex->pid);
		free(pipex);
		return (NULL);
	}
	init_pid(pipex->pid, pipex->count_cmd);
	return (pipex);
}
