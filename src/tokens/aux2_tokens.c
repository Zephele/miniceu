/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:57:38 by ratanaka          #+#    #+#             */
/*   Updated: 2025/05/30 17:44:03 by ratanaka         ###   ########.fr       */
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
