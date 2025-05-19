/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_down.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:41:30 by ratanaka          #+#    #+#             */
/*   Updated: 2024/11/12 19:19:00 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_puthex(unsigned int n, int *count)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n >= 16)
		ft_puthex(n / 16, count);
	write(1, &hex[n % 16], 1);
	(*count)++;
}

int	ft_putnbr_hex_down(int n)
{
	int		count;

	count = 0;
	ft_puthex((unsigned int)n, &count);
	return (count);
}
