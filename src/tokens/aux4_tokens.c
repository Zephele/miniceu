/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux4_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:33:57 by ratanaka          #+#    #+#             */
/*   Updated: 2025/07/22 15:45:53 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_empty_expand(char *temp, char *content, int *i, int *temp_i)
{		
	if (!temp)
	{
		free(content);
		return (1);
	}
	*i = *temp_i;
	return (0);
}

static char	*expand_interr(	char *temp_lstatus, int *i, char *temp)
{
	temp_lstatus = ft_itoa(gg()->last_status);
	temp = ft_strjoin_free(temp, temp_lstatus);
	(*i)++;
	free (temp_lstatus);
	return (temp);
}

char	*expand_aux(char *content, int *i, int *temp_size, char *temp)
{
	char		*expanded_content;
	char		*content_name;
	int			start;
	int			temp_i;
	static char	*temp_lstatus = NULL;

	start = *i;
	temp_i = *i;
	if (content[*i] == '?')
		return (expand_interr(temp_lstatus, i, temp));
	if (ft_isalpha(content[temp_i]) || content[temp_i] == '_')
	{
		temp_i++;
		while (content[temp_i] && (ft_isalnum_underline(content[temp_i])))
			temp_i++;
		content_name = ft_substr(content, start, temp_i - start);
		expanded_content = getenv(content_name);
		if (is_empty_expand(expanded_content, content_name, i, &temp_i))
			return (temp);
		temp = ft_strjoin_free(temp, expanded_content);
		*temp_size += ft_strlen(expanded_content);
		free(content_name);
	}
	*i = temp_i;
	return (temp);
}
