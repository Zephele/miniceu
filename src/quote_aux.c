/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:47:17 by ratanaka          #+#    #+#             */
/*   Updated: 2025/05/20 18:28:43 by ratanaka         ###   ########.fr       */
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

// void	concatenar_quotes(char *input, int start)
// {
	
// }
