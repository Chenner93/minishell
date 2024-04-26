/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckenaip <ckenaip@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:42:03 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/26 12:16:40 by ckenaip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_in_set(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	skip_charset(char *str, char *charset, size_t *i)
{
	while (check_in_set(str[*i], charset))
		(*i)++;
}

static int	x_split(char *str, char *sep)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	skip_charset(str, sep, &i);
	while (str[i])
	{
		while (str[i] && !check_in_set(str[i], sep))
		{
			if (check_in_set(str[i], "'\""))
				valid_quote_syntax(str, &i);
			else
				i++;
		}
		count++;
		while (str[i] && check_in_set(str[i], sep))
		{
			if (check_in_set(str[i], "'\""))
				valid_quote_syntax(str, &i);
			else
				i++;
		}
	}
	return (count);
}

static int	inter_split(char **split, char *str, size_t i, char *charset)
{
	int	z;
	int	y;

	z = -1;
	while (++z < x_split(str, charset))
	{
		y = i;
		while (str[i] && !check_in_set(str[i], charset))
		{
			if (str[i] == 34 || str[i] == 39)
				valid_quote_syntax(str, &i);
			else
				i++;
		}
		split[z] = ft_substr(str, y, i - y);
		if (split[z] == NULL)
			return (ft_free_array((void *)split), 1);
		while (str[i] && check_in_set(str[i], charset))
			i++;
	}
	return (0);
}

char	**split_minishell(char *str, char *charset)
{
	char	**split;
	int		i;

	if (str == NULL || charset == NULL)
		return (NULL);
	if (check_in_set(34, charset) || check_in_set(39, charset))
		return (NULL);
	split = malloc(sizeof(char *) * (x_split(str, charset) + 1));
	if (split == NULL)
		return (NULL);
	i = 0;
	while (str[i] && check_in_set(str[i], charset))
		i++;
	if (inter_split(split, str, i, charset) == 1)
		return (NULL);
	split[x_split(str, charset)] = NULL;
	return (split);
}

// virer le main un jour.


// int	main(int ac, char **av)
// {
// 	char	**split;
// 	int		count_split;

// 	if (ac != 3 || av[0] == NULL)
// 		return (printf("Need charset argument first, then the str to split\n"),
// 			0);
// 	count_split = x_split(av[2], av[1]);
// 	split = split_minishell(av[2], av[1]);
// 	if (split != NULL)
// 	{
// 		for (int i = 0; split[i]; i++)
// 		{
// 			printf("%s\n", split[i]);
// 			free(split[i]);
// 		}	
// 		free(split);
// 	}
// 	return (0);
// }
