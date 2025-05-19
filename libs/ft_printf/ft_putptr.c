/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:08:01 by ratanaka          #+#    #+#             */
/*   Updated: 2024/11/12 16:21:03 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(void *ptr)
{
	unsigned long	temp;
	int				count;
	int				i;
	char			hex[16];
	char			*str;

	count = 0;
	i = 0;
	str = "0123456789abcdef";
	temp = (unsigned long)ptr;
	if (temp != 0)
		count = count + ft_putstr("0x");
	if (temp == 0)
		return (write(1, "(nil)", 5));
	else
	{
		while (temp > 0)
		{
			hex[i++] = str[temp % 16];
			temp /= 16;
		}
	}
	while (i > 0)
		count += ft_putchar(hex[--i]);
	return (count);
}
