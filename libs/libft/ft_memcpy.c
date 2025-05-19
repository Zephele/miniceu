/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:31:31 by ratanaka          #+#    #+#             */
/*   Updated: 2024/10/25 16:49:30 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*temp;

	i = 0;
	temp = (char *)dest;
	if (!src && !dest)
	{
		return (NULL);
	}
	while (i < n)
	{
		temp[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}
