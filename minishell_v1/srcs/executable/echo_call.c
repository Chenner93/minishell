/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_call.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:18:28 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/09 09:47:55 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//done

static void	check_option(t_cmd *cmd_lst, int	*i, int *n_opt)
{
	if (ft_strlen(cmd_lst->cmd[1]) == 2 && cmd_lst->cmd[1]
		&& ft_strncmp(cmd_lst->cmd[1], "-n", 2) == 0)
	{
		*i = 2;
		*n_opt = 1;
	}
	else
	{
		*i = 1;
		*n_opt = 0;
	}
}

static void	dup_echo(int fd_in, int fd_out)
{
	if (fd_in != -2)
	{
		close(fd_in);
	}
	if (fd_out != -2)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

static void	children_echo(t_cmd *cmd_lst)
{
	int	i;
	int	n_opt;

	i = 0;
	n_opt = 0;
	check_option(cmd_lst, &i, &n_opt);
	dup_echo(cmd_lst->fd_in, cmd_lst->fd_out);
	while (cmd_lst->cmd[i])
	{
		printf("%s", cmd_lst->cmd[i]);
		i++;
		if (cmd_lst->cmd[i] != NULL)
			printf(" ");
	}
	if (n_opt == 0)
		printf("\n");
}

void	echo_call(t_pipex *pipex, t_cmd *cmd_lst)
{	
	int	pid;

	if (cmd_lst->fd_in == -1 || cmd_lst->fd_out == -1)
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		children_echo(cmd_lst);
		exit_child_perror(pipex, NULL, 0);
	}
	waitpid(pid, NULL, 0);
}
