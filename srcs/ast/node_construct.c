/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_construct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:11:58 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/26 18:38:57 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	link_nodes(t_ast_node *curr_node,
					t_ast_node **prev_node,
					char prev_dir)
{
	if ((*prev_node) != NULL)
	{
		curr_node->prev_node = (*prev_node);
		if (prev_dir == 'l')
			(*prev_node)->l_node = curr_node;
		else
			(*prev_node)->r_node = curr_node;
	}
	else
		(*prev_node) = curr_node;
}



// static t_ast_node	*node_construct_arg(t_ast_node *cmd_node,
// 									char **args)
// {
// 	(void) cmd_node;

// 	char	**test = get_array_of_cmd_args(args);

// 	for (int i = 0; *(test + i) ; i++)
// 		printf("%s\n", *(test + i));

// 	// (void) args;
// 	free(test);
// 	return (NULL);
// }

t_ast_node	*node_construct_sep(t_ast_node **prev_node,
							char prev_dir,
							t_type prioritie_type)
{
	t_ast_node	*new_node;

	new_node = init_node(prioritie_type);
	if (new_node == NULL)
		return (false);
	link_nodes(new_node, prev_node, prev_dir);
	return (new_node);
}

t_ast_node	*node_construct_cmd(char ***env_vars,
							t_ast_node **prev_node,
							char prev_dir,
							char *cmd)
{
	t_ast_node	*cmd_node;
	char	**arguments;
	char	**redirections;

	cmd_node = init_node(CMD);
	if (cmd_node == NULL)
		return (false);
	link_nodes(cmd_node, prev_node, prev_dir);
	arguments = NULL;
	redirections = NULL;


	if (!interpret_arguments(env_vars, splitted_cmd))
	{
		write_err("Allocation failed parsing commands\n");
		ft_free_array((void *) splitted_cmd);
		return (false);
	}


	node_construct_arg(cmd_node, splitted_cmd);

	ft_free_array((void *) splitted_cmd);

	return (cmd_node);
}

// t_ast_node	*node_construct_cmd(char ***env_vars,
// 							t_ast_node **prev_node,
// 							char prev_dir,
// 							char *cmd)
// {
// 	t_ast_node	*cmd_node;
// 	char	**splitted_cmd;

// 	cmd_node = init_node(CMD);
// 	splitted_cmd = split_minishell(cmd, "\t\v\n\f\r ");
// 	if (cmd_node == NULL || splitted_cmd == NULL)
// 		return (false);

// 	link_nodes(cmd_node, prev_node, prev_dir);


// 	if (!interpret_arguments(env_vars, splitted_cmd))
// 	{
// 		write_err("Allocation failed parsing commands\n");
// 		ft_free_array((void *) splitted_cmd);
// 		return (false);
// 	}


// 	node_construct_arg(cmd_node, splitted_cmd);

// 	ft_free_array((void *) splitted_cmd);

// 	return (cmd_node);
// }
