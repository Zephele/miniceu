/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:35:09 by ratanaka          #+#    #+#             */
/*   Updated: 2025/05/19 12:14:26 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int size)
{
	char	*s_copy;
	size_t	i;

	i = 0;
	s_copy = malloc((ft_strlen(s)) + 1);
	if (!s_copy)
		return (NULL);
	while (s[i] != '\0')
	{
		s_copy[i] = s[i];
		i++;
	}
	s_copy[size] = '\0';
	return (s_copy);
}
