/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:54:10 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/26 10:59:11 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	g_exit_value = -69;

// concat var d'env avec +=
// option -nnnnn -> -n
// $_ -> refait la derniere cmd
// env - i crash wtf?
// incrementer shslvl
// hardcoder le path (env -i -> ls doit fonctionner genre)
// verifier si > f fait nimp ou pas (juste une redirection vers un fichier)

static bool	handling_cmds(t_prompt *prompt,
					char ***env_vars)
{
	t_ast_node	*ast;
	char		*raw;

	ast = NULL;
	raw = NULL;
	raw = readline(prompt->prompt);
	if (raw == NULL)
		return (false);
	if (str_is_white_space(raw))
		return (true);
	add_history(raw);
	if (check_valid_cmd_syntax(raw))
	{
		if (!the_woodsman(env_vars, &raw, &ast, '\0'))
			return (write_err("Error constructing ast.\n"), false);
	}
	else
		printf("Invalid command syntax.\n");
	// if (ast != NULL)
		// main_exec(ast, env_vars);
	free_ast(ast);
	free(raw);
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	char				**env_vars;
	t_prompt			prompt;
	struct sigaction	sigact;
	struct termios		term;

	(void) argc;
	(void) argv;
	env_vars = init_env_vars(envp);
	if (env_vars == NULL)
		return (1);
	init_prompt(&env_vars, &prompt);
	init_signals_structs(&sigact, &term, &sig_handler);
	while (1)
	{
		set_prompt(&prompt);
		if (!handling_cmds(&prompt, &env_vars))
			break ;
	}
	rl_clear_history();
	if (env_vars != NULL)
		ft_free_array((void **) env_vars);
	return (0);
}
