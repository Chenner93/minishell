/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckenaip <ckenaip@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:26:52 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/05 14:09:22 by ckenaip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	close_fd_child(t_pipex *pipex)
{
	t_cmd	*cmd;
	int		i;

	cmd = pipex->first_node;
	while (cmd != NULL)
	{
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		cmd = cmd->next;
	}
	i = -1;
	while (++i < pipex->count_cmd)
	{
		if (pipex->fd[i][0] > -1)
			close(pipex->fd[i][0]);
		if (pipex->fd[i][1] > -1)
			close(pipex->fd[i][1]);
	}
}

static void	close_fd_parent(t_pipex *pipex)
{
	t_cmd	*cmd;
	int		i;

	cmd = pipex->first_node;
	while (cmd != NULL)
	{
		if (cmd->fd_in > -1)
			close(cmd->fd_in);
		if (cmd->fd_out > -1)
			close(cmd->fd_out);
		cmd = cmd->next;
	}
	i = -1;
	while (++i < pipex->count_cmd)
	{
		if (pipex->fd[i][0] > -1)
			close(pipex->fd[i][0]);
		if (pipex->fd[i][1] > -1)
			close(pipex->fd[i][1]);
	}
}

static void	unique_execve(t_pipex *pipex, t_cmd *cmd_lst)
{
	pipex->pid[0] = fork();
	if (pipex->pid[0] == -1)
	{
		perror("fork");
		return ;
	}
	if (pipex->pid[0] == 0)
	{
		if (cmd_lst->cmd_path == NULL && !cmd_lst->is_builtin)
		{
			close_fd_child(pipex);
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(cmd_lst->cmd[0], 2);
			exit_child_perror(pipex, NULL, 1);
		}
		dup_std(pipex, cmd_lst, 0);
		close_fd_child(pipex);
		if (execve(pipex->cmd_lst->cmd_path, pipex->cmd_lst->cmd,
				(*pipex->env_lst)) == -1)
			exit_child_perror(pipex, pipex->cmd_lst->cmd[0], 1);
	}
}

void	unique_cmd(t_pipex *pipex)
{
	if (!pipex->cmd_lst->is_builtin)
		unique_execve(pipex, pipex->cmd_lst);
	else
		builtin_check(pipex, pipex->cmd_lst, 0);
	close_fd_parent(pipex);
}
