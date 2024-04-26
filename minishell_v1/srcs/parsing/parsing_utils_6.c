/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:39:49 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/02 13:44:35 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool	write_here_doc(char ***env_vars,
					t_cmd *curr_node,
					char *delimiter)
{
	char	*line;
	char	*interpreted_line;
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	while (1)
	{
		line = readline(NULL);
		if (line == NULL)
			return (false);
		if (ft_strlen(line) == delimiter_len
			&& ft_strncmp(line, delimiter, delimiter_len) == 0)
			break ;
		interpreted_line = parse_interpreted_argument(env_vars, line);
		write(curr_node->fd_in, interpreted_line, ft_strlen(interpreted_line));
		write(curr_node->fd_in, "\n", 1);
		free(interpreted_line);
		free(line);
	}
	free(line);
	return (true);
}
