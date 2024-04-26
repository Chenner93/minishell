/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckenaip <ckenaip@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:52:43 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/08 16:31:03 by ckenaip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		**fd;
	int		*pid;
	int		fd_in;
	int		fd_out;
	int		count_cmd;
	t_cmd	*cmd_lst;
	t_cmd	*first_node;
	char	***env_lst;
}	t_pipex;

/*****   MAIN_EXEC   *****/
int		main_exec(t_cmd *cmd_lst, char ***env_lst);
/*****   INIT_PIPE   *****/
t_pipex	*init_cmd_pipe(t_cmd *cmd_lst, char ***env_lst);
/*******   PIPEX   *******/
void	pipex(t_pipex *pipex);
/***   BUILTIN_CHECK   ***/
void	builtin_check(t_pipex *pipex, t_cmd *cmd_lst,
			int index_cmd);
/***   CALL_BUILTIN   ****/
void	cd_call(t_cmd *cmd_lst, int index_cmd);
void	echo_call(t_pipex *pipex, t_cmd *cmd_lst);
void	pwd_call(t_cmd *cmd_lst);
void	env_call(char ***env_lst);
void	export_call(t_cmd *cmd_lst, char ***env_vars);
void	unset_call(t_cmd *cmd_lst, char ***env_lst);
void	exit_call(t_pipex *pipex);
/****   UNIQUE_CMD   *****/
void	unique_cmd(t_pipex *pipex);
/****   MULTIPLE_CMD   ***/
void	multiple_cmd(t_pipex *pipex);
/******   DUP_STD   ******/
void	dup_std(t_pipex *pipex, t_cmd *cmd_lst, int i);
/****   EXIT_PERROR   ****/
void	exit_child_perror(t_pipex *pipex, char *message, int out);
void	clean_up_pipe(t_pipex *pipex, int in_child);

#endif