/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:32:00 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/03/27 23:10:12 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

typedef struct s_cmd
{
	bool			is_builtin;
	char			*cmd_path;
	char			**cmd;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}	t_cmd;

/** cmd_utils_1.c */
t_cmd	*cmd_init(void);

void	free_cmds(t_cmd *cmds_lst);

#endif