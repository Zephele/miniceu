/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:47:17 by ratanaka          #+#    #+#             */
/*   Updated: 2025/05/22 16:02:06 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	asux_seen_quotes(char *input, int *i, int *quotes, char quote)
{
	if (input[*i] == quote)
	{
		(*i)++;
		(*quotes)++;
		while (input[*i] != '\0' && input[*i] != quote)
			(*i)++;
		if (input[*i] == quote)
			(*quotes)++;
		if (*quotes == 2)
			*quotes = 0;
	}
}

int	seen_quotes(char *input, int i)
{
	int	quote;
	int	dquote;


	quote = 0;
	dquote = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
			asux_seen_quotes(input, &i, &quote, '\'');
		if (input[i] == '\"')
			asux_seen_quotes(input, &i, &dquote, '\"');
		i++;
	}
	if (quote == 1 || dquote == 1)
		return (1);
	return (0);
}

char	*include_quotes(char *content, char quote)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	temp = malloc((ft_strlen(content)) + 3);
	if (!temp)
	{
		free (content);
		return (NULL);
	}
	temp[i] = quote;
	i++;
	while (content[j] != '\0')
	{
		temp[i] = content[j];
		i++;
		j++;
	}
	temp[i] = quote;
	temp[++i] = '\0';
	free(content);
	return (temp);
}
