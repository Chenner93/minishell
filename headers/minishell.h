/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:54:34 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/25 14:13:09 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/** External headers include */
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <termios.h>

/** Headers include. */
# include "../libft/libft.h"
# include "env.h"
# include "prompt.h"
# include "signals.h"
# include "ast_node.h"
# include "parsing.h"
# include "syntax.h"

/** write_err.c */
void	write_err(char *err);

#endif