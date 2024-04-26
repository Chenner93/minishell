/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:08:02 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/09 10:49:04 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// >
static void	trunc_redirection(t_cmd *curr_node,
							char *file)
{
	if (curr_node->fd_out >= 0)
		close(curr_node->fd_out);
	curr_node->fd_out = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
}

// >>
static void	append_redirection(t_cmd *curr_node,
							char *file)
{
	if (curr_node->fd_out >= 0)
		close(curr_node->fd_out);
	curr_node->fd_out = open(file, O_CREAT | O_APPEND | O_WRONLY, 0777);
}

// <
static void	in_redirection(t_cmd *curr_node,
						char *file)
{
	if (curr_node->fd_in >= 0)
		close(curr_node->fd_in);
	curr_node->fd_in = open(file, O_RDONLY, 0777);
	if (curr_node->fd_in == -1)
		perror("Minishell");
}

// <<
static bool	here_doc_redirection(char ***env_vars,
							t_cmd *curr_node,
							char *delimiter)
{
	if (curr_node->fd_in >= 0)
		close(curr_node->fd_in);
	unlink(HERE_DOC);
	curr_node->fd_in = open(HERE_DOC, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (curr_node->fd_in == -1)
	{
		perror("here_doc_msh");
		return (false);
	}
	if (!write_here_doc(env_vars, curr_node, delimiter))
	{
		unlink(HERE_DOC);
		return (false);
	}
	close(curr_node->fd_in);
	curr_node->fd_in = open(HERE_DOC, O_RDONLY, 0777);
	return (true);
}

bool	handle_redirection(char ***env_vars,
						t_cmd *curr_node,
						char *redir_type,
						char *redir_arg)
{
	if (*(redir_type) == '>' && *(redir_type + 1) != '>')
		trunc_redirection(curr_node, redir_arg);
	else if (*(redir_type) == '>' && *(redir_type + 1) == '>')
		append_redirection(curr_node, redir_arg);
	else if (*(redir_type) == '<' && *(redir_type + 1) != '<')
		in_redirection(curr_node, redir_arg);
	else if (*(redir_type) == '<' && *(redir_type + 1) == '<')
	{
		if (!here_doc_redirection(env_vars, curr_node, redir_arg))
			return (false);
	}
	return (true);
}
