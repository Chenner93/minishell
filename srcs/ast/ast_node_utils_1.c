/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:30:44 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/26 17:06:22 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_ast_node	*init_node(t_type type)
{
	t_ast_node	*new_ast_node;

	new_ast_node = (t_ast_node *) malloc(sizeof(t_ast_node));
	if (new_ast_node == NULL)
		return (NULL);
	new_ast_node->type = type;
	new_ast_node->is_builtin = false;
	new_ast_node->cmd_path = NULL;
	new_ast_node->cmd = NULL;
	new_ast_node->infile = NULL;
	new_ast_node->outfile = NULL;
	new_ast_node->l_node = NULL;
	new_ast_node->r_node = NULL;
	new_ast_node->prev_node = NULL;
	return (new_ast_node);
}

static void	free_node(t_ast_node *ast_node)
{
	if (ast_node->cmd_path != NULL)
		free(ast_node->cmd_path);
	if (ast_node->cmd != NULL)
		ft_free_array((void **) ast_node->cmd);
	if (ast_node->infile != NULL)
		free(ast_node->infile);
	if (ast_node->outfile != NULL)
		free(ast_node->outfile);

	// a tester.
	if (ast_node->type == HERE_DOC)
		unlink(ast_node->infile);

	free(ast_node);
}

void	free_ast(t_ast_node *ast)
{
	if (ast == NULL)
		return ;
	if (ast->l_node != NULL)
		free_ast(ast->l_node);
	if (ast->r_node != NULL)
		free_ast(ast->r_node);
	free_node(ast);
}
