/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_call.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckenaip <ckenaip@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:16:41 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/08 14:20:50 by ckenaip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//special case with only CD not manage because not asked
//Done
//If redirection fuck d'up, do not do it !!!

void	cd_call(t_cmd *cmd_lst, int index_cmd)
{
	if (index_cmd != 0 || cmd_lst->next != NULL)
		return ;
	if (cmd_lst->cmd[1] == NULL)
		return ;
	if (cmd_lst->cmd[2] != NULL)
	{
		printf("cd: too many arguments\n");
		chdir("");
		return ;
	}
	if (chdir(cmd_lst->cmd[1]) != 0)
		perror("cd");
}
