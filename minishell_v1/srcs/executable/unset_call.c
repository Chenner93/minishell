/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_call.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckenaip <ckenaip@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 08:57:47 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/05 11:01:09 by ckenaip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	reorganize_env_lst(char ***env_lst, size_t len)
{
	size_t	i;
	size_t	y;

	i = 0;
	while (i < len)
	{
		if ((*env_lst)[i] == NULL)
		{
			y = i;
			while ((*env_lst)[y] == NULL && y < len)
				y++;
			(*env_lst)[i] = (*env_lst)[y];
			(*env_lst)[y] = NULL;
		}
		i++;
	}
}

static ssize_t	find_pos_var(char **env_lst, char *cmd,
			size_t len_cmd, size_t len_lstenv)
{
	size_t	i;

	i = 0;
	while (i < len_lstenv)
	{
		if (env_lst[i] != NULL
			&& ft_strncmp(env_lst[i], cmd, len_cmd) == 0
			&& env_lst[i][len_cmd] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	unset_call(t_cmd *cmd_lst, char ***env_lst)
{
	size_t	len_var;
	size_t	len_lstenv;
	size_t	newlen_lstenv;
	ssize_t	pos_var;
	int		i;

	i = 1;
	len_lstenv = ft_get_array_length((void **)*env_lst);
	while (cmd_lst->cmd[i])
	{
		len_var = ft_strlen(cmd_lst->cmd[i]);
		pos_var = find_pos_var((*env_lst), cmd_lst->cmd[i],
				len_var, len_lstenv);
		if (pos_var != -1)
		{
			free((*env_lst)[pos_var]);
			(*env_lst)[pos_var] = NULL;
		}
		i++;
	}
	reorganize_env_lst(env_lst, len_lstenv);
	newlen_lstenv = ft_get_array_length((void **)*env_lst);
	(*env_lst) = (char **)ft_realloc_array((void **)(*env_lst),
			len_lstenv * sizeof(char *), (newlen_lstenv + 1) * sizeof(char *));
}
