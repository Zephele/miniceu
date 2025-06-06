/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:57:38 by ratanaka          #+#    #+#             */
/*   Updated: 2025/06/06 17:34:32 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	validate_syntax_aux(t_token *current, t_token *prev)
{
	if (current->type == PIPE && (!prev || prev->type == PIPE))
	{
		ft_putstr_fd("Syntax error near '|'\n", STDERR_FILENO);
		return (1);
	}
	if ((current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == REDIR_APPEND || current->type == HEREDOC)
		&& (!current->next || (current->next->type
				!= ARG && current->next->type != CMD)))
	{
		ft_putstr_fd("Syntax error near '", STDERR_FILENO);
		ft_putstr_fd(current->content, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	validate_syntax(t_token *tokens)
{
	t_token	*current;
	t_token	*prev;

	if (!tokens)
		return (1);
	current = tokens;
	prev = NULL;
	while (current)
	{
		if (validate_syntax_aux(current, prev))
			return (1);
		prev = current;
		current = current->next;
	}
	if (prev && prev->type == PIPE)
	{
		ft_putstr_fd("Syntax error: pipe at end\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

t_token	*handle_env(char *input, int *i)
{
	t_token	*token;
	int		start;

	start = *i;
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	while (input[*i] && !ft_strchr(" <>|", input[*i]))
		(*i)++;
	token->content = ft_substr(input, start, *i - start);
	token->type = ENV;
	token->next = NULL;
	return (token);
}

char	*expand_env_vars(char *content)
{
	int		i;
	int		start;
	char	*temp;
	char	*expanded_content;
	char	*content_name;

	i = 0;
	while (content[i])
	{
		while (content[i] && content[i] != '$')
			i++;
		if (content[i] == '$')
		{
			start = i;
			i++;
			if (ft_isalpha(content[i]) || content[i] == '_')
			{
				temp = ft_substr(content, 0, i);
				while (content[i] && (ft_isalnum(content[i]) || content[i] == '_'))
					i++;
				content_name = ft_substr(content, start, i - start);
				expanded_content = getenv(content_name);
				free(content);
				return (expanded_content);
			}
		}
	}
}

char	*expand_env_vars(char *content)
{
	int		i;
	int		j;
	int		start;
	char	*temp;
	char	*expanded_content;
	char	*content_name;

	i = 0;
	while (content[i])
	{
		while (content[i] && content[i] != '$')
		{
			temp[i] = content[i];
			i++;
		}
		if (content[i] == '$')
		{
			start = i;
			i++;
			if (ft_isalpha(content[i]) || content[i] == '_')
			{
				while (content[i] && (ft_isalnum(content[i])))
					i++;
				content_name = ft_substr(content, start, i - start);
				expanded_content = getenv(content_name);
				j = 0;
				while (j < ft_strlen(expanded_content))
				{
					temp[start] = expanded_content[j];
					j++;
					start++;
				}
			}
		}
	}
}
