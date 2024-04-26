/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:54:34 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/03/27 02:33:13 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/** External headers include */
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

/** Headers include. */
# include "../libft/libft.h"
# include "env.h"
# include "prompt.h"
# include "signals.h"
# include "cmd.h"
# include "syntax.h"
# include "parsing.h"
# include "utils.h"
# include "exec.h"

#endif