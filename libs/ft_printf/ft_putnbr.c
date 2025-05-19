/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:51:11 by ratanaka          #+#    #+#             */
/*   Updated: 2024/11/12 19:35:14 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	write_0_int_min(int n)
{
	if (n == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	return (0);
}

static int	is_negative(int n)
{
	return (n < 0);
}

int	ft_putnbr(int n)
{
	char	buffer[11];
	int		i;
	int		negative;

	i = 10;
	negative = is_negative(n);
	if (n == 0 || n == -2147483648)
	{
		return (write_0_int_min(n));
	}
	if (negative)
	{
		n = -n;
		write(1, "-", 1);
	}
	while (n > 0)
	{
		buffer[i--] = ((n % 10) + '0');
		n = n / 10;
	}
	write(1, &buffer[i + 1], 10 - i);
	if (negative)
		return (11 - i);
	return (10 - i);
}
