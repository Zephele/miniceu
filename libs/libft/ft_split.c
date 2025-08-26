/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pede-jes <pede-jes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:26:42 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/25 19:40:06 by pede-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	total_words;

	total_words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			total_words++;
		while (*s && *s != c)
			s++;
	}
	return (total_words);
}

static void	free_str(char **str, size_t i)
{
	while (i <= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

static void	fill_substring_array(char **str, const char *s, char c)
{
	const char	*temp;
	size_t		i;

	temp = s;
	i = 0;
	while (*temp)
	{
		while (*s == c)
			s++;
		temp = s;
		while (*temp && *temp != c)
			temp++;
		if (*temp == c || temp > s)
		{
			*str = ft_substr(s, 0, temp - s);
			if (*str == (void *)0)
				free_str(str, i);
			s = temp;
			str++;
			i++;
		}
	}
	*str = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		size;

	if (!s)
		return (NULL);
	size = count_words(s, c);
	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	fill_substring_array(new, s, c);
	if (!new)
		return (NULL);
	return (new);
}
