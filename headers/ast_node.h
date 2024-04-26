/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:32:00 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/25 11:54:00 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_NODE_H
# define AST_NODE_H

typedef enum s_type
{
	AND,
	OR,
	PIPE,
	CMD,
	ARG,
	APPEND,
	TRUNC,
	IN,
	HERE_DOC
}	t_type;

typedef struct s_ast_node
{
	t_type				type;
	bool				is_builtin;
	char				*cmd_path;
	char				**cmd;
	char				*infile;
	char				*outfile;
	struct s_ast_node	*l_node;
	struct s_ast_node	*r_node;
	struct s_ast_node	*prev_node;
}	t_ast_node;

/** ast_node__utils_1.c */
t_ast_node	*init_node(t_type type);

void		free_ast(t_ast_node *ast);

/** ast_priorities.c */
size_t		get_highest_priorities(char *raw);

t_type		get_prioritie_type(char *str,
				size_t index_sep);

/** node_construct.c */
t_ast_node	*node_construct_sep(t_ast_node **prev_node,
				char prev_dir,
				t_type prioritie_type);

t_ast_node	*node_construct_cmd(char ***env_vars,
				t_ast_node **prev_node,
				char prev_dir,
				char *cmd);

/** ast_construct.c */
bool	the_woodsman(char ***env_vars,
					char **str,
					t_ast_node **prev,
					char prev_dir);

#endif