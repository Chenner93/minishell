/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:29:33 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/03/06 11:43:40 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	realloc_line(t_line *line,
			size_t line_size,
			size_t new_line_size)
{
	line->line = ft_realloc(line->line,
			sizeof(char) * line_size,
			sizeof(char) * new_line_size);
}

static bool	fill_line(t_line *line,
				t_buffer *buffer)
{
	while (buffer->buffer_iter < BUFFER_SIZE)
	{
		*((char *) line->line + line->line_iter)
			= *((char *) buffer->buffer + buffer->buffer_iter);
		if (*((char *) buffer->buffer + buffer->buffer_iter) == '\n')
		{
			buffer->buffer_iter++;
			return (true);
		}
		if (*((char *) buffer->buffer + buffer->buffer_iter) == '\0')
		{
			buffer->buffer_iter = 0;
			return (true);
		}
		buffer->buffer_iter++;
		line->line_iter++;
	}
	return (false);
}

static ssize_t	fill_buffer(int fd,
					t_buffer *buffer,
					t_line *line,
					size_t *refill)
{
	ssize_t	read_status;

	read_status = 1;
	if (buffer->buffer_iter == 0 || buffer->buffer_iter == BUFFER_SIZE)
	{
		buffer->buffer_iter = 0;
		read_status = read(fd, buffer->buffer, BUFFER_SIZE);
		if (read_status == -1)
		{
			ft_bzero(buffer->buffer, BUFFER_SIZE);
			if (line->line != NULL)
				free(line->line);
		}
		else
		{
			*((char *) buffer->buffer + read_status) = '\0';
			(*refill)++;
		}
	}
	return (read_status);
}

static char	*return_line(t_line *line,
				size_t refill)
{
	if (*((char *) line->line) == '\0')
		return (free(line->line), NULL);
	realloc_line(line, (refill + 1) * BUFFER_SIZE, line->line_iter + 2);
	if (line->line == NULL)
		return (NULL);
	*((char *) line->line + line->line_iter + 1) = '\0';
	return ((char *) line->line);
}

char	*get_next_line(int fd)
{
	static t_buffer	buffer;
	t_line			line;
	size_t			refill;

	if (fd < 0 || fd > 1023)
		return (NULL);
	line.line = NULL;
	line.line_iter = 0;
	refill = 0;
	while (1)
	{
		if (fill_buffer(fd, &buffer, &line, &refill) == -1)
			return (NULL);
		realloc_line(&line, refill * BUFFER_SIZE, (refill + 1) * BUFFER_SIZE);
		if (line.line == NULL)
			return (NULL);
		if (fill_line(&line, &buffer))
			return (return_line(&line, refill));
	}
	return (NULL);
}
