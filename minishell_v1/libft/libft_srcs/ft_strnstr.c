/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:11:23 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/01/16 11:31:05 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	s2_len;
	size_t	i;
	size_t	j;

	i = 0;
	s2_len = ft_strlen(s2);
	if (s2_len == 0)
		return (&*((char *)s1));
	while (i < len && *(s1 + i) != '\0')
	{
		j = 0;
		while (*(s1 + i + j) == *(s2 + j) && j < s2_len && (i + j) < len)
			j++;
		if (j == s2_len)
			return (&*((char *)s1 + i));
		i++;
	}
	return (0);
}
