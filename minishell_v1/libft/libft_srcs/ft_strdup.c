/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:42:19 by maja              #+#    #+#             */
/*   Updated: 2024/01/16 11:31:05 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	char	*s2;
	int		i;

	s2 = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (*(s + i) != '\0')
	{
		*(s2 + i) = *(s + i);
		i++;
	}
	*(s2 + i) = '\0';
	return (s2);
}
