/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:58:29 by ratanaka          #+#    #+#             */
/*   Updated: 2024/10/18 11:50:21 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*temp;

	i = 0;
	temp = (char *)dest;
	if (!src && !dest)
		return (NULL);
	if ((temp < (const char *)src) || (temp > (const char *)src + n))
	{
		while (i < n)
		{
			temp[i] = ((const char *)src)[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			temp[i - 1] = ((const char *)src)[i - 1];
			i--;
		}
	}
	return (dest);
}
