/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckenaip <ckenaip@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:59:07 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/26 19:15:55 by ckenaip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*name_here_doc(void)
{
	static int	i = 0;
	char		*itoa_char;
	char		*to_return;

	itoa_char = ft_itoa(i);
	to_return = ft_strjoin("/tmp/.here_doc", itoa_char);
	free(itoa_char);
	i++;
	return (to_return);
}

char	*here_doc(char *delimiter, char ***env_var)
{
	//ouvrir et ecrire dans le here doc
	//creer un nom de here doc
    //char *ft parse_arg(char ***env_var, char *str)
	int		fd;
	char	*name;
	char	*line;

	name = name_here_doc();
	
	fd = open(name, O_CREAT, O_TRUNC, O_RDWR, 0644);
	if (fd < 0)
		return (free(name), perror("fd"), NULL);
	line = get_next_line(0);
	while (line != NULL && ft_strncmp(line, delimiter, ft_strlen(delimiter)))
	{
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	close(fd);
	free(line);
	return (name);
}
