/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:54:10 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/09 11:59:34 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	g_exit_value = 0;

// concat var d'env avec +=
// option -nnnnn -> -n
// $_ -> refait la derniere cmd
// virer le write chelou la dans export
// env - i crash wtf?
// incrementer shslvl
// hardcoder le path (env -i -> ls doit fonctionner genre)

static void	print_linked_list(t_cmd *cmds)
{
	t_cmd	*tmp = cmds;

	while (tmp != NULL)
	{
		printf("is_builtin: %i\n", tmp->is_builtin);
		printf("cmd_path: %s\n", tmp->cmd_path);
		size_t	i = 0;
		if (tmp->cmd != NULL)
		{
			while (tmp->cmd[i] != NULL)
			{
				printf("%s+", tmp->cmd[i]);
				i++;
			}
		}
		printf("\n");
		printf("fd_in: %i\n", tmp->fd_in);
		printf("fd_out: %i\n", tmp->fd_out);
		tmp = tmp->next;
	}
}

static bool	handling_cmds(t_prompt *prompt,
					char ***env_vars)
{
	t_cmd	*cmds_lst;
	char	*raw_input;

	cmds_lst = NULL;
	raw_input = NULL;
	raw_input = readline(prompt->prompt);
	if (raw_input == NULL)
		return (false);
	if (!cmd_is_empty(raw_input))
	{
		add_history(raw_input);
		if (check_valid_cmd_syntax(raw_input))
			cmds_lst = parse_cmds(env_vars, raw_input);
		else
			printf("Invalid command syntax.\n");
	}
	print_linked_list(cmds_lst);
	main_exec(cmds_lst, env_vars);
	free_cmds(cmds_lst);
	free(raw_input);
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt			prompt;
	struct sigaction	sigact;
	char				**env_vars;

	(void) argc;
	(void) argv;
	init_prompt(&prompt);
	set_sigact_struct(&sigact, &sig_handler);
	env_vars = init_env_vars(envp);
	while (1)
	{
		set_prompt(&prompt);
		if (!handling_cmds(&prompt, &env_vars))
			break ;
	}
	rl_clear_history();
	if (env_vars != NULL)
		free_array((void **) env_vars);
	return (0);
}
