/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeiffer <gpeiffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:48:23 by gpeiffer          #+#    #+#             */
/*   Updated: 2024/01/17 08:34:45 by gpeiffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	va_start(args, format);
	len = iter_format(format, args, 0, 0);
	va_end(args);
	return (len);
}

int	iter_format(const char *f, va_list args, size_t i, size_t l)
{
	while (*(f + i) != '\0')
	{
		if (f[i] == '%' && f[i + 1] == 'c')
			l += ft_putchar(va_arg(args, int));
		else if (f[i] == '%' && f[i + 1] == 's')
			l += ft_putstr(va_arg(args, char *));
		else if (f[i] == '%' && f[i + 1] == 'p')
			l += print_prefixed_hexa(va_arg(args, unsigned long long));
		else if (f[i] == '%' && (f[i + 1] == 'd' || f[i + 1] == 'i'))
			l += print_nb(va_arg(args, int));
		else if (f[i] == '%' && f[i + 1] == 'u')
			l += print_positive_nb(va_arg(args, unsigned int));
		else if (f[i] == '%' && f[i + 1] == 'x')
			l += print_hexa(va_arg(args, unsigned int), 0);
		else if (f[i] == '%' && f[i + 1] == 'X')
			l += print_hexa(va_arg(args, unsigned int), 1);
		else if (f[i] == '%' && f[i + 1] == '%')
			l += ft_putchar('%');
		else
			l += ft_putchar(f[i]);
		if (f[i] == '%')
			i++;
		i++;
	}
	return (l);
}
