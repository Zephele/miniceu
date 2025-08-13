/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:18:33 by ratanaka          #+#    #+#             */
/*   Updated: 2024/11/06 18:00:17 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	temp;
	int	negative;
	int	i;

	temp = 0;
	negative = 1;
	i = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	while (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			negative = -1;
		nptr ++;
		i++;
	}
	if (i > 1)
		return (0);
	while (*nptr != '\0' && (*nptr >= '0' && *nptr <= '9'))
	{
		temp = temp * 10 + (*nptr - '0');
		nptr++;
	}
	return (temp * negative);
}
