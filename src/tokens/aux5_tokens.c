/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux5_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pede-jes <pede-jes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:46:47 by pede-jes          #+#    #+#             */
/*   Updated: 2025/08/25 19:56:29 by pede-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	condition(char *input, int i, char quote)
{
	return ((input[i] && input[i] != ' ' && input[i] == quote)
		|| input[i] == '$');
}

static int	handle_quote_case(char *input, int *i, char quote, char **content)
{
	int		start;
	char	*temp;

	start = ++(*i);
	while (input[*i] && input[*i] != quote)
		(*i)++;
	temp = ft_substr(input, start - 1, *i - start + 2);
	if (is_empty(temp, *content))
		return (0);
	*content = ft_strjoin_free(*content, temp);
	if (quote == '"' || temp[0] == '"')
		*content = expand_env_vars(*content);
	free(temp);
	if (input[*i] == quote)
		(*i)++;
	else
		return (2);
	return (1);
}

static int	handle_dollar_case(char *input, int *i, char quote, char **content)
{
	int		start;
	char	*temp;

	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	temp = ft_substr(input, start, *i - start);
	if (is_empty(temp, *content))
		return (0);
	*content = ft_strjoin_free(*content, temp);
	if (quote == '"' || temp[0] == '"')
		*content = expand_env_vars(*content);
	free(temp);
	return (1);
}

char	*extract_quoted_content(char *input, int *i, char quote)
{
	char	*content;
	int		status;

	content = ft_strdup("");
	while (condition(input, *i, quote))
	{
		if (input[*i] == quote)
			status = handle_quote_case(input, i, quote, &content);
		else
			status = handle_dollar_case(input, i, quote, &content);
		if (status == 0)
			return (NULL);
		if (status == 2)
			break ;
	}
	return (content);
}
