/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:47:17 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/25 18:23:56 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	asux_seen_quotes(char *input, int *i, int *quotes, char quote)
{
	if (input[*i] == quote)
	{
		if (input[*i + 1])
			(*i)++;
		else
		{
			(*quotes)++;
			(*i)++;
			return ;
		}
		(*quotes)++;
		while (input[*i] != '\0' && input[*i] != quote)
			(*i)++;
		if (input[*i] == quote)
			(*quotes)++;
		if (*quotes == 2)
			*quotes = 0;
	}
	(*i)++;
}

static int	aux_seen_redirerror(char *input, int i)
{
	if ((input[i] == '<' && input[i] == '>')
		&& (input[i] == '>' && input[i] == '<'))
	{
		ft_putstr_fd("Error: SyntaxError\n", STDERR_FILENO);
		return (1);
	}
	if ((input[i] == '<' || input[i] == '>')
		&& (input[i + 1] == '<' || input[i + 1] == '>'))
	{
		if (input[i + 2] == '<' || input[i + 2] == '>')
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

char	*extract_quoted_content(char *input, int *i, char quote)
{
	int		start;
	int		theres_quote;
	char	*temp;
	char	*content;

	content = ft_strdup("");
	while ((input[*i] != '\0' && input[*i] != ' ' && input[*i] == quote)
		|| input[*i] == '$')
	{
		if (input[*i] == quote)
		{
			theres_quote = (*i);
			start = ++(*i);
		}
		else
		{
			theres_quote = (*i);
			start = (*i);
		}
		while (input[*i] != '\0' && input[*i] != quote)
			(*i)++;
		if (input[theres_quote] == quote)
		{
			temp = ft_substr(input, (start - 1), *i - (start - 2));
			if (is_empty(temp, content))
				return (NULL);
			content = ft_strjoin_free(content, temp);
			if (quote == '"' || temp[0] == '"')
				content = expand_env_vars(content);
			free(temp);
			if (input[*i] == quote)
				(*i)++;
			else
				break ;
		}
		else
		{
			temp = ft_substr(input, start, *i - start);
			if (is_empty(temp, content))
				return (NULL);
			content = ft_strjoin_free(content, temp);
			if (quote == '"' || temp[0] == '"')
				content = expand_env_vars(content);
			free(temp);
		}
	}
	return (content);
}
