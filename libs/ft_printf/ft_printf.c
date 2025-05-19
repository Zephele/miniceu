/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:16:03 by ratanaka          #+#    #+#             */
/*   Updated: 2024/11/14 12:47:53 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	convert(char specifier, va_list args)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += ft_putchar(va_arg(args, int));
	if (specifier == 's')
		count += ft_putstr(va_arg(args, char *));
	if (specifier == 'p')
		count += ft_putptr(va_arg(args, void *));
	if ((specifier == 'd') || (specifier == 'i'))
		count += ft_putnbr(va_arg(args, int));
	if (specifier == 'u')
		count += ft_putnbr_unsigned(va_arg(args, unsigned int));
	if (specifier == 'x')
		count += ft_putnbr_hex_down(va_arg(args, int));
	if (specifier == 'X')
		count += ft_putnbr_hex_upper(va_arg(args, int));
	if (specifier == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	int			i;
	int			count;

	i = 0;
	count = 0;
	va_start(args, str);
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += convert(str[i + 1], args);
			i++;
		}
		else
		{
			ft_putchar(str[i]);
			count ++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
