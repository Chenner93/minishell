/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:58:22 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/26 18:32:30 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// static size_t	count_args(char **args)
// {
// 	size_t	i;
// 	size_t	count;

// 	i = 0;
// 	count = 0;
// 	while (*(args + i) != NULL)
// 	{
// 		if (is_cmd_file_redir(*(*(args + i))))
// 			i++;
// 		else
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

// char	**get_array_of_cmd_args(char **args)
// {
// 	char	**result;
// 	size_t	args_iter;
// 	size_t	result_iter;

// 	result = (char **) malloc(sizeof(char *) * (count_args(args) + 1));
// 	if (result == NULL)
// 		return (NULL);
// 	args_iter = 0;
// 	result_iter = 0;
// 	while (*(args + args_iter) != NULL)
// 	{
// 		if (is_cmd_file_redir(*(*(args + args_iter))))
// 		{
// 			args_iter+=2;
// 			continue ;
// 		}
// 		*(result + result_iter) = *(args + args_iter);
// 		args_iter++;
// 		result_iter++;
// 	}
// 	*(result + result_iter) = NULL;
// 	return (result);
// }
