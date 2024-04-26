/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:28:25 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/11 10:42:04 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool	str_is_white_space(char *raw_cmd)
{
	size_t	i;

	i = 0;
	while (*(raw_cmd + i) != '\0')
	{
		if (*(raw_cmd + i) > 32)
			return (false);
		i++;
	}
	return (true);
}
