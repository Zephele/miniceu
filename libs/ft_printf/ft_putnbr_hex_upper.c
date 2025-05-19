/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_upper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:20:45 by ratanaka          #+#    #+#             */
/*   Updated: 2024/11/12 19:27:19 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_puthex_upper(unsigned int n, int *count)
{
	char	*hex_upper;

	hex_upper = "0123456789ABCDEF";
	if (n >= 16)
		ft_puthex_upper(n / 16, count);
	write(1, &hex_upper[n % 16], 1);
	(*count)++;
}

int	ft_putnbr_hex_upper(int n)
{
	int	count;

	count = 0;
	ft_puthex_upper((unsigned int)n, &count);
	return (count);
}
