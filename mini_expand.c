/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:35:58 by ratanaka          #+#    #+#             */
/*   Updated: 2025/06/09 17:02:10 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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

int	ft_strlen1(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

int	is_empty(char *temp, char *content)
{		
	if (!temp)
	{
		free(content);
		return (1);
	}
	return (0);
}

static char	*expand_aux(char *content, int *i, int *temp_size, char *temp)
{
	char	*expanded_content;
	char	*content_name;
	int		start;
	int		temp_i;

	start = *i;
	temp_i = *i;
	if (ft_isalpha(content[temp_i]) || content[temp_i] == '_')
	{
		temp_i++;
		while (content[temp_i] && (ft_isalnum(content[temp_i])))
			temp_i++;
		content_name = ft_substr(content, start, temp_i - start);
		expanded_content = getenv(content_name);
		if (is_empty(expanded_content, content_name))
		{
			*i = temp_i;
			return (temp);
		}
		temp = ft_strjoin_free(temp, expanded_content);
		*temp_size += ft_strlen1(expanded_content);
		free(content_name);
	}
	*i = temp_i;
	return (temp);
}

char	*expand_env_vars(char *content)
{
	int		i;
	int		temp_size;
	char	*temp;

	i = 0;
	temp_size = 0;
	temp = ft_strdup("");
	while (content[i])
	{
		while (content[i] && content[i] != '$')
		{
			temp = ft_strjoin_free(temp, (char []){content[i], '\0'});
			i++;
			temp_size++;
		}
		if (content[i] == '$')
		{
			i++;
			temp = expand_aux(content, &i, &temp_size, temp);
		}
	}
	return (temp);
}

int	main(void)
{
	char	*content;

	content = "     Hello $USERasd, welcome to the shell!";
	content = expand_env_vars(content);
	ft_printf("Expanded content: %s\n", content);
	free(content);
	return (0);
}
