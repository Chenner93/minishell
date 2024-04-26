/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:44:18 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/03/26 20:02:28 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	set_username(char *user)
{
	char	*user_env_var;

	user_env_var = getenv("USER");
	ft_bzero(user, 64);
	if (user_env_var == NULL || ft_strlen(user_env_var) > 64)
	{
		ft_strlcpy(user, "username", 9);
		return ;
	}
	ft_strlcpy(user, user_env_var, ft_strlen(user_env_var) + 1);
}

static void	set_hostname(char *host)
{
	char	*session_manager;
	size_t	i;

	session_manager = getenv("SESSION_MANAGER");
	ft_bzero(host, 64);
	if (session_manager == NULL)
	{
		ft_strlcpy(host, "hostname", 9);
		return ;
	}
	while (*(session_manager) != '/' && *(session_manager + 1) != '\0')
		session_manager++;
	session_manager++;
	i = 0;
	while (*(session_manager) != '.' && *(session_manager) != '\0')
	{
		*(host + i) = *session_manager;
		if (i >= 63)
			break ;
		session_manager++;
		i++;
	}
}

void	init_prompt(t_prompt *prompt)
{
	set_username(prompt->user);
	set_hostname(prompt->host);
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
