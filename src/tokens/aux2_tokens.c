/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:57:38 by ratanaka          #+#    #+#             */
/*   Updated: 2025/06/10 17:06:54 by ratanaka         ###   ########.fr       */
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

char	*expand_aux(char *content, int *i, int *temp_size, char *temp)
{
	char	*expanded_content;
	char	*content_name;
	int		start;
	int		temp_i;

	start = *i;
	temp_i = *i;
	if (ft_isalpha(content[temp_i]) || content[temp_i] == '_')
	{
		temp_i++;
		while (content[temp_i] && (ft_isalnum_underline(content[temp_i])))
			temp_i++;
		content_name = ft_substr(content, start, temp_i - start);
		expanded_content = getenv(content_name);
		if (is_empty(expanded_content, content_name))
		{
			*i = temp_i;
			return (temp);
		}
		temp = ft_strjoin_free(temp, expanded_content);
		*temp_size += ft_strlen(expanded_content);
		free(content_name);
	}
	*i = temp_i;
	return (temp);
}

char	*expand_env_vars(char *content)
{
	int		i;
	int		temp_size;
	char	*temp;

	i = 0;
	temp_size = 0;
	temp = ft_strdup("");
	while (content[i])
	{
		while (content[i] && content[i] != '$')
		{
			temp = ft_strjoin_free(temp, (char []){content[i], '\0'});
			i++;
			temp_size++;
		}
		if (content[i] == '$')
		{
			i++;
			temp = expand_aux(content, &i, &temp_size, temp);
		}
	}
	free(content);
	return (temp);
}
