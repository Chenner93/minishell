/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:35:02 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/10 11:09:28 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool	is_white_space(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}

bool	is_redirection_char(int c)
{
	if (c == 60 || c == 62 || c == 124)
		return (true);
	return (false);
}

// liste a completer probablement..
bool	is_forbidden_char(int c)
{
	if (c == 60 || c == 62 || c == 124 || c == 38 || c == 40 || c == 41
		|| c == 35 || c == 59 || c == 0)
		return (true);
	return (false);
}

bool	is_valid_env_var(char *arg)
{
	if (*(arg) == '\0' || *(arg + 1) == '\0')
		return (false);
	if (*(arg + 1) == '?' || ft_isalpha(*(arg + 1)) == 1024)
		return (true);
	return (false);
}
