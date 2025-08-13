/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:19:43 by ratanaka          #+#    #+#             */
/*   Updated: 2024/10/24 11:46:36 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*temp;
	char	*save;

	temp = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	save = temp;
	if (!temp)
		return (NULL);
	while (*s1 != '\0')
	{
		*temp = *s1;
		s1++;
		temp++;
	}
	if (*s1 == '\0')
	{
		while (*s2 != '\0')
		{
			*temp = *s2;
			s2++;
			temp++;
		}
	}
	*temp = '\0';
	return (save);
}
