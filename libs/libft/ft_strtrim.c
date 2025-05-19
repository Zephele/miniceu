/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:47:47 by ratanaka          #+#    #+#             */
/*   Updated: 2024/11/06 14:21:13 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*temp;
	size_t	start;
	size_t	end;
	size_t	len;

	start = 0;
	end = (ft_strlen(s1));
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	len = end - start;
	temp = malloc(len + 1);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, s1 + start, len + 1);
	return (temp);
}
