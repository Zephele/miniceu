/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:50:34 by ratanaka          #+#    #+#             */
/*   Updated: 2025/05/19 14:22:46 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	schar_aux(char *input, int *i, t_token *token)
{
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
			token->type = REDIR_APPEND;
		else
			token->type = REDIR_OUT;
	}
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
			token->type = HEREDOC;
		else
			token->type = REDIR_IN;
	}
	if (((input[*i] == '>') && (input[*i + 1] == '>'))
		|| ((input[*i] == '<') && (input[*i + 1] == '<')))
		*i += 2;
	else
		*i += 1;
}

static t_token	*handle_schar(char *input, int *i)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = NULL;
	if (input[*i] == '>' && input[*i + 1] == '>')
		token->content = ft_strdup(">>");
	else if (input[*i] == '<' && input[*i + 1] == '<')
		token->content = ft_strdup("<<");
	else
		token->content = ft_strndup(&input[*i], 1);
	if (input[*i] == '>' || input[*i] == '<')
		schar_aux(input, i, token);
	else
	{
		token->type = PIPE;
		*i += 1;
	}
	token->next = NULL;
	return (token);
}

// static t_token	*handle_quotes(char *input, int *i, char quote)
// {
// 	t_token	*token;
// 	int		start;

// 	start = *i;
// 	token = (t_token *)malloc(sizeof(t_token));
// 	if (!token)
// 		return (NULL);
// }

static t_token	*handle_general(char *input, int *i)
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
	token->type = CMD;
	token->next = NULL;
	return (token);
}

t_token	*tokenize(char *input)
{
	t_token	*head;
	t_token	**current;
	int		i;
	int		len;

	head = NULL;
	current = &head;
	i = 0;
	len = ft_strlen(input);
	while (i < len)
	{
		if (input[i] == ' ')
			i++;
		else if (ft_strchr("<>|", input[i]))
			*current = handle_schar(input, &i);
		else
			*current = handle_general(input, &i);
		if (*current)
			current = &(*current)->next;
	}
	return (head);
}
