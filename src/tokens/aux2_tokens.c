/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pede-jes <pede-jes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:57:38 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/25 19:57:07 by pede-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	validate_syntax_aux(t_token *current, t_token *prev)
{
	if (current->type == PIPE && (!prev || prev->type == PIPE))
	{
		gg()->last_status = 2;
		ft_putstr_fd("Syntax error near '|'\n", STDERR_FILENO);
		return (1);
	}
	if ((current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == REDIR_APPEND || current->type == HEREDOC)
		&& (!current->next || (current->next->type
				!= ARG && current->next->type != CMD
				&& current->next->type != ENV)))
	{
		gg()->last_status = 2;
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
		gg()->last_status = 2;
		ft_putstr_fd("Syntax error: pipe at end\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

static char	*expand_dollar(char *temp, int *temp_size, int *i, char *content)
{
	char	*temp2;

	temp2 = ft_strdup(temp);
	free (temp);
	(*i)++;
	if (content[*i] == ' ' || !content[*i]
		|| content[*i] == '"' || content[*i] == '\'')
		temp2 = ft_strjoin_free(temp2, "$");
	else if (content[*i] == '?')
		temp2 = expand_aux(content, i, temp_size, temp2);
	else
		temp2 = expand_aux(content, i, temp_size, temp2);
	return (temp2);
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
			temp = expand_dollar(temp, &temp_size, &i, content);
	}
	free_safe(content);
	return (temp);
}
