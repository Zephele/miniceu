/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux3_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pede-jes <pede-jes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 21:01:22 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/26 11:58:11 by pede-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*aux_quotes(char *input, int *i, char quote, char *content)
{
	char	*temp;

	quote = input[*i];
	if ((input[*i] == '\'' || input[*i] == '\"'))
	{
		quote = input[*i];
		if (!content)
			content = extract_quoted_content(input, i, quote);
		else
		{
			temp = extract_quoted_content(input, i, quote);
			content = ft_strjoin_free(content, temp);
			free (temp);
		}
	}
	return (content);
}

char	*aux_general(char *input, int *i, char *content)
{
	char	*temp;
	int		start;

	start = *i;
	while (input[*i] && input[*i] != '\''
		&& input[*i] != '\"' && !ft_strchr(" <>|", input[*i]))
	{
		if (!content)
		{
			while (input[*i] && !ft_strchr(" <>|\"\'", input[*i]))
				(*i)++;
			content = ft_substr(input, start, *i - start);
			content = expand_env_vars(content);
		}
		else
		{
			while (input[*i] && !ft_strchr(" <>|\"\'", input[*i]))
				(*i)++;
			temp = ft_substr(input, start, *i - start);
			content = ft_strjoin_free(content, temp);
			free (temp);
		}
	}
	return (content);
}


