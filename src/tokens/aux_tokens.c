/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pede-jes <pede-jes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:47:17 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/28 13:51:30 by pede-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	asux_seen_quotes(char *input, int *i, int *quotes, char quote)
{
	if (input[*i] == quote)
	{
		(*quotes)++;
		(*i)++;
		if (input[*i] == '\0')
			return ;
		while (input[*i] != '\0' && input[*i] != quote)
			(*i)++;
		if (input[*i] == quote)
		{
			(*quotes)++;
			(*i)++;
		}
		if (*quotes == 2)
			*quotes = 0;
	}
}
static int	aux_seen_redirerror(char *input, int i)
{
	int	len;

	len = ft_strlen(input);
	if (i + 1 < len)
	{
		if ((input[i] == '<' && input[i + 1] == '>') ||
			(input[i] == '>' && input[i + 1] == '<'))
		{
			ft_putstr_fd("Error: SyntaxError\n", STDERR_FILENO);
			return (1);
		}
		if (i + 2 < len && (input[i] == '<' || input[i] == '>') &&
			(input[i + 1] == '<' || input[i + 1] == '>') &&
			(input[i + 2] == '<' || input[i + 2] == '>'))
		{
			ft_putstr_fd("Error: SyntaxError\n", STDERR_FILENO);
			return (1);
		}
	}
	return (0);
}

int	seen_quotes(char *input, int i)
{
	int	quote;
	int	dquote;

	quote = 0;
	dquote = 0;
	while (input[i] != '\0')
	{
		if (aux_seen_redirerror(input, i))
			return (1);
		else if (input[i] == '\'')
			asux_seen_quotes(input, &i, &quote, '\'');
		else if (input[i] == '\"')
			asux_seen_quotes(input, &i, &dquote, '\"');
		else if (input[i] == '\\' && input[i + 1])
			i = i + 2;
		else
			i++;
	}
	if (quote == 1 || dquote == 1)
	{
		ft_putstr_fd("Error: unclosed quote\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
