/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux3_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 21:01:22 by ratanaka          #+#    #+#             */
/*   Updated: 2025/06/23 18:17:41 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*aux_quotes(char *input, int *i, char quote, char *content)
{
	char	*temp;

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
