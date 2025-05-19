/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:54:27 by ratanaka          #+#    #+#             */
/*   Updated: 2024/10/21 12:28:17 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*temp;

	i = 0;
	temp = (char *)s;
	if (!(char)c)
		return (&temp[ft_strlen(temp)]);
	while (temp[i] != '\0')
	{
		if (temp[i] == (char)c)
			return (temp + i);
		i ++;
	}
	return (NULL);
}
