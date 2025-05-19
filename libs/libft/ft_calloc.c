/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:45:49 by ratanaka          #+#    #+#             */
/*   Updated: 2024/10/30 16:11:26 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	char	*temp;
	size_t	i;
	size_t	total;

	i = 0;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	total = (nmemb * size);
	if (total / nmemb != size)
		return (NULL);
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	temp = (char *)ptr;
	while (i < (total))
	{
		temp[i] = 0;
		i++;
	}
	return (temp);
}
