/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:06:48 by ratanaka          #+#    #+#             */
/*   Updated: 2024/11/04 11:22:38 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*temp;

	temp = (char *)s;
	i = ((ft_strlen(temp) - 1));
	if (!(char)c)
		return (&temp[ft_strlen(temp)]);
	if (!*s)
		return (NULL);
	while (i > 0)
	{
		if (temp[i] == (char)c)
		{
			return (temp + i);
		}
		i--;
	}
	if (temp[i] == (char)c)
		return (temp + i);
	return (NULL);
}
