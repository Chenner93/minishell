/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckenaip <ckenaip@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:41:52 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/08 16:30:43 by ckenaip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// typedef struct s_cmd
// {
// 	bool			is_builtin;
// 	char			*cmd_path;
// 	char			**cmd;
// 	int				fd_in;
// 	int				fd_out;
// 	struct s_cmd	*next;
// }	t_cmd;

void	builtin_check(t_pipex *pipex, t_cmd *cmd_lst,
			int index_cmd)
{
	if (ft_strncmp(cmd_lst->cmd[0], "echo", 5) == 0)
		echo_call(pipex, cmd_lst);
	else if (ft_strncmp(cmd_lst->cmd[0], "cd", 3) == 0)
		cd_call(cmd_lst, index_cmd);
	else if (ft_strncmp(cmd_lst->cmd[0], "pwd", 4) == 0)
		pwd_call(cmd_lst);
	else if (ft_strncmp(cmd_lst->cmd[0], "env", 4) == 0)
		env_call(pipex->env_lst);
	else if (ft_strncmp(cmd_lst->cmd[0], "export", 7) == 0)
		export_call(cmd_lst, pipex->env_lst);
	else if (ft_strncmp(cmd_lst->cmd[0], "unset", 6) == 0)
		unset_call(cmd_lst, pipex->env_lst);
	else if (ft_strncmp(cmd_lst->cmd[0], "exit", 5) == 0)
		exit_call(pipex);
}
