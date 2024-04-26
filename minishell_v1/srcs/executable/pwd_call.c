/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_call.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckenaip <ckenaip@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:21:47 by ckenaip           #+#    #+#             */
/*   Updated: 2024/03/24 19:58:36 by ckenaip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//fonctionnel in pipe
// maybe return 1

void	pwd_call(t_cmd *cmd_lst)
{
	char	buffer[9999];

	if (cmd_lst == NULL)
		return ;
	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		perror("getcwd");
		return ;
	}
	printf("%s\n", buffer);
}
