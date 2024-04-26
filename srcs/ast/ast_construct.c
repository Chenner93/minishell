/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_construct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:07:29 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/26 18:16:47 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool	the_woodsman(char ***env_vars,
					char **str,
					t_ast_node **prev,
					char prev_dir)
{
	/**
	 * Potentiellement modifier cette fonction pour que si la construction
	 * d'un node CMD echoue, on arrete la construction de l'arbre.
	 * (si un node echoue, la recursive break mais si cetais sur la 
	 * branche de gauche, la branche de droite ce construit quand meme.)
	*/
	t_ast_node	*curr_node;
	size_t		prio_index;
	char		*left_str;
	char		*right_str;

	if (!remove_useless_parenthesis(str))
		return (false);
	left_str = NULL;
	right_str = NULL;
	prio_index = get_highest_priorities((*str));
	if (prio_index != 0)
	{
		curr_node = node_construct_sep(prev, prev_dir,
				get_prioritie_type((*str), prio_index));
		if (curr_node == NULL)
			return (false);
		if (!the_axe((*str), &left_str, &right_str, prio_index))
			return (false);
		if (!the_woodsman(env_vars, &left_str, &curr_node, 'l')
			|| !the_woodsman(env_vars, &right_str, &curr_node, 'r'))
			return (free(left_str), free(right_str), false);
		return (free(left_str), free(right_str), true);
	}
	curr_node = node_construct_cmd(env_vars, prev, prev_dir, (*str));
	return (curr_node != NULL);
}
