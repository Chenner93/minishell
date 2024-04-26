/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_std.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:12:47 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/09 10:59:04 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	dup_beg(t_pipex *pipex, t_cmd *cmd_lst, int i)
{
	if (cmd_lst->fd_in == -2)
	{
		if (dup2(0, STDIN_FILENO) == -1)
			exit_child_perror(pipex, NULL, 1);
	}
	else
	{
		if (dup2(cmd_lst->fd_in, STDIN_FILENO) == -1)
			exit_child_perror(pipex, NULL, 1);
	}
	if (cmd_lst->fd_out == -2)
	{
		if (dup2(pipex->fd[i][1], STDOUT_FILENO) == -1)
			exit_child_perror(pipex, NULL, 1);
	}
	else
	{
		if (dup2(cmd_lst->fd_out, STDOUT_FILENO) == -1)
			exit_child_perror(pipex, NULL, 1);
	}
}

static void	dup_mid(t_pipex *pipex, t_cmd *cmd_lst, int i)
{
	if (cmd_lst->fd_in == -2)
	{
		if (dup2(pipex->fd[i - 1][0], STDIN_FILENO) == -1)
			exit_child_perror(pipex, NULL, 1);
	}
	else
	{
		if (dup2(cmd_lst->fd_in, STDIN_FILENO) == -1)
			exit_child_perror(pipex, NULL, 1);
	}
	if (cmd_lst->fd_out == -2)
	{
		if (dup2(pipex->fd[i][1], STDOUT_FILENO) == -1)
			exit_child_perror(pipex, NULL, 1);
	}
	else
	{
		if (dup2(cmd_lst->fd_out, STDOUT_FILENO) == -1)
			exit_child_perror(pipex, NULL, 1);
	}
}

static void	dup_end(t_pipex *pipex, t_cmd *cmd_lst, int i)
{
	if (cmd_lst->fd_in == -2)
	{
		if (dup2(pipex->fd[i - 1][0], STDIN_FILENO) == -1)
			exit_child_perror(pipex, NULL, 1);
	}
	else
	{
		if (dup2(cmd_lst->fd_in, STDIN_FILENO) == -1)
			exit_child_perror(pipex, NULL, 1);
	}
	if (cmd_lst->fd_out == -2)
	{
		if (dup2(1, STDOUT_FILENO) == -1)
			exit_child_perror(pipex, NULL, 1);
	}
	else
	{
		if (dup2(cmd_lst->fd_out, STDOUT_FILENO) == -1)
			exit_child_perror(pipex, NULL, 1);
	}
}

static void	dup_unique_cmd(t_pipex *pipex, t_cmd *cmd_lst)
{
	if (cmd_lst->fd_in != -2)
	{
		if (dup2(cmd_lst->fd_in, STDIN_FILENO) == -1)
			exit_child_perror(pipex, NULL, 0);
	}
	else
	{
		if (dup2(0, STDIN_FILENO) == -1)
			exit_child_perror(pipex, NULL, 0);
	}
	if (cmd_lst->fd_out != -2)
	{
		if (dup2(cmd_lst->fd_out, STDOUT_FILENO) == -1)
			exit_child_perror(pipex, NULL, 0);
	}
	else
	{
		if (dup2(1, STDOUT_FILENO) == -1)
			exit_child_perror(pipex, NULL, 0);
	}
}

void	dup_std(t_pipex *pipex, t_cmd *cmd_lst, int i)
{
	if (pipex->count_cmd > 1)
	{
		if (i == 0)
			dup_beg(pipex, cmd_lst, i);
		else if (i < pipex->count_cmd - 1)
			dup_mid(pipex, cmd_lst, i);
		else
			dup_end(pipex, cmd_lst, i);
	}
	else
		dup_unique_cmd(pipex, cmd_lst);
}
