/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 06:48:38 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/25 15:01:47 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// static ssize_t	count_env_var_name_len(char *arg)
// {
// 	ssize_t	i;

// 	i = 0;
// 	while (*(arg + i) != '\0' && *(arg + i) != '=')
// 	{
// 		if (is_white_space(*(arg + i)))
// 			return (-1);
// 		i++;
// 	}
// 	if (*(arg + i) != '=')
// 		return (-1);
// 	return (i);
// }

// static size_t	count_env_var_value_len(char *arg)
// {
// 	size_t	i;
// 	size_t	count;

// 	i = 0;
// 	count = 0;
// 	skip_white_space_iterator_incr(arg, &i);
// 	while (*(arg + i) != '\0')
// 	{
// 		if (is_white_space(*(arg + i)))
// 		{
// 			skip_white_space_iterator_incr(arg, &i);
// 			if (*(arg) != '\0')
// 				count++;
// 			continue ;
// 		}
// 		i++;
// 		count++;
// 	}
// 	return (count);
// }

// static void	cpy_env_var_value(char *arg,
// 						char *value)
// {
// 	char	white_space;
// 	size_t	i;
// 	size_t	y;

// 	i = 0;
// 	y = 0;
// 	skip_white_space_iterator_incr(arg, &i);
// 	while (*(arg + i) != '\0')
// 	{
// 		if (is_white_space(*(arg + i)))
// 		{
// 			white_space = *(arg + i);
// 			skip_white_space_iterator_incr(arg, &i);
// 			if (*(arg + i) != '\0')
// 			{
// 				*(value + y) = white_space;
// 				y++;
// 			}
// 			continue ;
// 		}
// 		*(value + y) = *(arg + i);
// 		i++;
// 		y++;
// 	}
// 	*(value + y) = '\0';
// }

// char	*parse_env_var_name(char *arg)
// {
// 	char	*name;
// 	ssize_t	name_len;

// 	name_len = count_env_var_name_len(arg);
// 	if (name_len == -1)
// 		return (NULL);
// 	name = (char *) malloc(sizeof(char) * (name_len + 1));
// 	if (name == NULL)
// 		return (NULL);
// 	ft_strlcpy(name, arg, name_len + 1);
// 	return (name);
// }

// char	*parse_env_var_value(char *arg)
// {
// 	char	*value;
// 	size_t	value_len;

// 	value_len = count_env_var_value_len(arg);
// 	value = (char *) malloc(sizeof(char) * (value_len + 1));
// 	if (value == NULL)
// 		return (NULL);
// 	cpy_env_var_value(arg, value);
// 	return (value);
// }
