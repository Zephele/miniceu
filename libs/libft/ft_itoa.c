/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:59:45 by ratanaka          #+#    #+#             */
/*   Updated: 2024/11/06 15:54:47 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	num;

	num = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		num++;
	}
	return (num);
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

char	*ft_itoa(int n)
{
	char	*temp;
	int		i;
	int		negative;

	negative = is_negative(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (negative)
		n = -n;
	i = count_digits(n);
	temp = malloc(i + negative + 1);
	if (!temp)
		return (NULL);
	if (negative)
		temp[0] = '-';
	temp[i + negative] = '\0';
	i = i + negative - 1;
	while (n > 0)
	{
		temp[i--] = ((n % 10) + '0');
		n = n / 10;
	}
	if (negative == 0 && i == 0)
		temp[0] = '0';
	return (temp);
}
