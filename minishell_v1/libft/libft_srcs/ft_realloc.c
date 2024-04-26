/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:35:25 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/03/06 11:40:46 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_realloc(void *ptr,
			size_t ptr_size,
			size_t new_ptr_size)
{
	void	*new_ptr;

	new_ptr = malloc(new_ptr_size);
	if (new_ptr == NULL)
	{
		if (ptr != NULL)
			free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (new_ptr);
	if (ptr_size > new_ptr_size)
		ft_memcpy_opti_af(new_ptr, ptr, new_ptr_size);
	else
		ft_memcpy_opti_af(new_ptr, ptr, ptr_size);
	return (free(ptr), new_ptr);
}
