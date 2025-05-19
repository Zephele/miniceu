/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:58:02 by ratanaka          #+#    #+#             */
/*   Updated: 2024/11/05 11:59:33 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	s_size;

	i = 0;
	s_size = ft_strlen(s);
	if ((!s))
		return (NULL);
	if (len > s_size - start)
		len = ((s_size - start));
	if (start >= s_size)
		return (ft_strdup(""));
	substr = (char *)malloc(len + 1);
	if ((!substr))
		return (NULL);
	while (i < len)
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}
