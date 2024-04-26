/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:44:18 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/26 11:16:20 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	set_username(char ***env_vars,
					char *user)
{
	char	*current_user;

	current_user = get_value_by_name(env_vars, "USER");
	if (current_user == NULL)
		ft_strlcpy(user, "username", 9);
	else if (ft_strlen(current_user) > 63)
	{
		ft_strlcpy(user, "username", 9);
		free(current_user);
	}
	else
	{
		ft_strlcpy(user, current_user, ft_strlen(current_user) + 1);
		free(current_user);
	}
}

static void	set_hostname(char ***env_vars,
					char *host)
{
	char	*current_host;
	size_t	i;
	size_t	y;

	current_host = get_value_by_name(env_vars, "SESSION_MANAGER");
	if (current_host == NULL)
	{
		ft_strlcpy(host, "hostname", 9);
		return ;
	}
	y = 0;
	while (*(current_host + y) != '/' && *(current_host + y + 1) != '\0')
		y++;
	y++;
	i = 0;
	while (*(current_host + y) != '.' && *(current_host + y) != '\0')
	{
		*(host + i) = *(current_host + y);
		if (i > 63)
			break ;
		y++;
		i++;
	}
	free(current_host);
}

void	init_prompt(char ***env_vars,
				t_prompt *prompt)
{
	ft_bzero(prompt->user, 64);
	ft_bzero(prompt->host, 64);
	set_username(env_vars, prompt->user);
	set_hostname(env_vars, prompt->host);
	getcwd(prompt->curr_path, 512);
}

void	set_prompt(t_prompt *prompt)
{
	size_t	user_len;
	size_t	host_len;
	size_t	path_len;

	getcwd(prompt->curr_path, 512);
	user_len = ft_strlen(prompt->user);
	host_len = ft_strlen(prompt->host);
	path_len = ft_strlen(prompt->curr_path);
	ft_bzero(prompt->prompt, 640);
	ft_strlcpy(prompt->prompt, prompt->user, user_len + 1);
	*(prompt->prompt + user_len) = '@';
	ft_strlcpy(prompt->prompt + user_len + 1, prompt->host, host_len + 1);
	*(prompt->prompt + user_len + host_len + 1) = ':';
	ft_strlcpy(prompt->prompt + user_len + host_len + 2,
		prompt->curr_path, path_len + 1);
	ft_strlcpy(prompt->prompt + user_len + host_len + path_len + 2, "$ ", 3);
}
