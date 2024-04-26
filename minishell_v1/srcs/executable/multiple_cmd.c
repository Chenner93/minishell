/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckenaip <ckenaip@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:41:42 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/05 14:05:16 by ckenaip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// if (!cmd_lst->is_builtin)
	// {
	// 	pipex(pipe);
	// }
	// else
	// {
	// 	builtin_check(cmd_lst, i);
	// }

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

static int	children_process(t_pipex *pipex, t_cmd *cmd_lst, int i)
{
	if (cmd_lst->cmd_path == NULL && !cmd_lst->is_builtin)
	{
		close_fd_child(pipex);
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(cmd_lst->cmd[i], 2);
		exit_child_perror(pipex, NULL, 1);
		return (1);
	}
	dup_std(pipex, cmd_lst, i);
	close_fd_child(pipex);
	if (cmd_lst->is_builtin)
	{
		builtin_check(pipex, cmd_lst, i);
		exit_child_perror(pipex, NULL, 0);
	}
	else
	{
		if (execve(pipex->cmd_lst->cmd_path, pipex->cmd_lst->cmd,
				(*pipex->env_lst)) == -1)
			exit_child_perror(pipex, pipex->cmd_lst->cmd[0], 1);
	}
	return (0);
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

void	multiple_cmd(t_pipex *pipex)
{
	int		i;

	i = 0;
	while (pipex->cmd_lst != NULL)
	{
		if (pipe(pipex->fd[i]) == -1)
		{
			perror("pipe");
			break ;
		}
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
		{
			perror("fork");
			break ;
		}
		if (pipex->pid[i] == 0)
		{
			if (children_process(pipex, pipex->cmd_lst, i) == 1)
				break ;
		}
		i++;
		pipex->cmd_lst = pipex->cmd_lst->next;
	}
	close_fd_parent(pipex);
}
