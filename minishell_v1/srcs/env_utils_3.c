/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 06:48:38 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/04 10:50:55 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static ssize_t	count_env_var_name_len(char *arg)
{
	ssize_t	i;

	i = 0;
	while (*(arg + i) != '\0' && *(arg + i) != '=')
	{
		if (is_white_space(*(arg + i)))
			return (-1);
		i++;
	}
	if (*(arg + i) != '=')
		return (-1);
	return (i);
}

char	*parse_env_var_name(char *arg)
{
	char	*name;
	ssize_t	name_len;

	name_len = count_env_var_name_len(arg);
	if (name_len == -1)
		return (NULL);
	name = (char *) malloc(sizeof(char) * (name_len + 1));
	if (name == NULL)
		return (NULL);
	ft_strlcpy(name, arg, name_len + 1);
	return (name);
}

static size_t	count_env_var_value_len(char *arg)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	skip_white_space_iterator_incr(arg, &i);
	while (*(arg + i) != '\0')
	{
		if (is_white_space(*(arg + i)))
		{
			skip_white_space_iterator_incr(arg, &i);
			if (*(arg) != '\0')
				count++;
			continue ;
		}
		i++;
		count++;
	}
	return (count);
}

static void	cpy_env_var_value(char *arg,
						char *value)
{
	char	white_space;
	size_t	i;

	i = 0;
	skip_white_space_pointer_incr(&arg);
	while (*(arg) != '\0')
	{
		if (is_white_space(*(arg)))
		{
			white_space = *(arg);
			skip_white_space_pointer_incr(&arg);
			if (*(arg) != '\0')
			{
				*(value + i) = white_space;
				i++;
			}
			continue ;
		}
		*(value + i) = *(arg);
		i++;
		arg++;
	}
	*(value + i) = '\0';
}

char	*parse_env_var_value(char *arg)
{
	char	*value;
	size_t	value_len;

	value_len = count_env_var_value_len(arg);
	value = (char *) malloc(sizeof(char) * (value_len + 1));
	if (value == NULL)
		return (NULL);
	cpy_env_var_value(arg, value);
	return (value);
}
