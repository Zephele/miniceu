/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:47:17 by ratanaka          #+#    #+#             */
/*   Updated: 2025/05/26 11:34:18 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		if (input[i] == '\'')
			asux_seen_quotes(input, &i, &quote, '\'');
		if (input[i] == '\"')
			asux_seen_quotes(input, &i, &dquote, '\"');
		i++;
	}
	if (quote == 1 || dquote == 1)
	{
		ft_putstr_fd("Error: unclosed quote\n", STDERR_FILENO);
		return (1);
	}
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

char	*extract_quoted_content(char *input, int *i, char quote)
{
	int		start;
	char	*temp;
	char	*content;

	content = ft_strdup("");
	while (input[*i] != '\0' && input[*i] != ' ' && input[*i] == quote)
	{
		start = ++(*i);
		while (input[*i] != '\0' && input[*i] != quote)
			(*i)++;
		temp = ft_substr(input, start, *i - start);
		if (!temp)
		{
			free(content);
			return (NULL);
		}
		content = ft_strjoin_free(content, temp);
		free(temp);
		if (input[*i] == quote)
			(*i)++;
		else
			break ;
	}
	return (content);
}
