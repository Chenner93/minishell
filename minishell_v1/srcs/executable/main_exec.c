/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckenaip <ckenaip@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:01:10 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/15 08:54:27 by ckenaip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_exit_value;

// typedef struct s_cmd
// {
// 	bool			is_builtin;
// 	char			*cmd_path;
// 	char			**cmd;
// 	int				fd_in;
// 	int				fd_out;
// 	struct s_cmd	*next;
// }	t_cmd;

static void	management_exit_status(t_pipex *pipex)
{
	int	i;
	int	status;

	status = 0;
	i = -1;
	while (++i < pipex->count_cmd)
	{
		if (pipex->pid[i] != -1)
			waitpid(pipex->pid[i], &status, 0);
		if (WIFEXITED(status))
			g_exit_value = WEXITSTATUS(status);
		else
			g_exit_value = 127;
	}
}

int	main_exec(t_cmd *cmd_lst, char ***env_lst)
{
	t_pipex	*pipex;

	if (cmd_lst == NULL)
		return (0);
	pipex = init_cmd_pipe(cmd_lst, env_lst);
	if (pipex == NULL)
		return (printf("Error malloc\n"), 0);
	if (pipex->count_cmd == 1)
		unique_cmd(pipex);
	else
		multiple_cmd(pipex);
	management_exit_status(pipex);
	clean_up_pipe(pipex, 0);
	return (0);
}
