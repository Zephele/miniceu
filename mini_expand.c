/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:35:58 by ratanaka          #+#    #+#             */
/*   Updated: 2025/06/06 18:00:05 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	ft_strlen1(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*expand_env_vars(char *content)
{
	int		i;
	int		temp_size = 0;
	int		j;
	int		start;
	char	*temp = ft_strdup("");
	char	*expanded_content;
	char	*content_name;

	i = 0;
	while (content[i])
	{
		while (content[i] && content[i] != '$')
		{
			temp[temp_size] = content[i];
			i++;
			temp_size++;
		}
		if (content[i] == '$')
		{
			i++;
			start = i;
			if (ft_isalpha(content[i]) || content[i] == '_')
			{
				while (content[i] && (ft_isalnum(content[i])))
					i++;
				content_name = ft_substr(content, start, i - start);
				expanded_content = getenv(content_name);
				j = 0;
				while (j < ft_strlen1(expanded_content))
				{
					temp[temp_size] = expanded_content[j];
					j++;
					temp_size++;
				}
			}
		}
	}
	return (temp);
}

int	main(void)
{
	char	*content;

	content = "a $USER, wasdasda";
	content = expand_env_vars(content);
	ft_printf("Expanded content: %s\n", content);
}
