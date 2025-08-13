/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:38:25 by ratanaka          #+#    #+#             */
/*   Updated: 2024/11/06 17:38:14 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_0_int_min(int n, int fd)
{
	if (n == 0)
	{
		write(fd, "0", 1);
	}
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
}

static int	is_negative(int n)
{
	int	negative;

	negative = 0;
	if (n < 0)
	{
		negative = 1;
	}
	return (negative);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	buffer[12];
	int		i;
	int		negative;

	i = 11;
	negative = is_negative(n);
	if (n == 0 || n == -2147483648)
	{
		write_0_int_min(n, fd);
		return ;
	}
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		buffer[i--] = ((n % 10) + '0');
		n = n / 10;
	}
	if (negative == 1)
	{
		buffer[0] = '-';
		write(fd, &buffer[0], 1);
	}
	write(fd, &buffer[i + 1], 11 - i);
}
