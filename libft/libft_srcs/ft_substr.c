/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 09:36:39 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/04/18 13:37:55 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	char	*calc(char const *s, char *s2, unsigned int start, size_t len);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;

	s2 = 0;
	if (s == 0)
		return (0);
	if (start >= ft_strlen(s))
	{
		s2 = (char *) malloc(sizeof(char) * 1);
		if (s2 == NULL)
			return (NULL);
		*(s2) = '\0';
		return (s2);
	}
	return (calc(s, s2, start, len));
}

static	char	*calc(char const *s, char *s2, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(s) > start)
	{
		while (*(s + start + i) != '\0' && i < len)
			i++;
	}
	s2 = (char *) malloc(sizeof(char) * i + 1);
	if (s2 == NULL)
		return (NULL);
	while (j < i)
	{
		*(s2 + j) = *(s + start + j);
		j++;
	}
	*(s2 + j) = '\0';
	return (s2);
}
