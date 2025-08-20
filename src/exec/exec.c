/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:33:14 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/20 13:37:33 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_biut(t_token *tokens)
{
	if (!tokens || !tokens->content)
		return (0);
	if (compare_aux(tokens->content, "echo") == 0
		|| compare_aux(tokens->content, "cd") == 0
		|| compare_aux(tokens->content, "exit") == 0
		|| compare_aux(tokens->content, "env") == 0
		|| compare_aux(tokens->content, "unset") == 0
		|| compare_aux(tokens->content, "export") == 0
		|| compare_aux(tokens->content, "pwd") == 0)
		return (1);
	return (0);
}

int	there_is_redir(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (!current)
		return (0);
	while (current)
	{
		if (current->type == 2 || current->type == 3
			|| current->type == 4 || current->type == 5)
			return (1);
		else
			current = current->next;
	}
	return (0);
}

t_token	*exec_biut(t_token *tokens)
{
	if (compare_aux(tokens->content, "echo") == 0)
		return (ft_echo(&tokens));
	else if (compare_aux(tokens->content, "cd") == 0)
		return (ft_cd(&tokens));
	else if (compare_aux(tokens->content, "exit") == 0)
	{
		ft_exit(&tokens);
		return (NULL);
	}
	else if (compare_aux(tokens->content, "env") == 0)
		return (ft_env(&tokens));
	else if (compare_aux(tokens->content, "export") == 0)
		return (ft_export(&tokens));
	else if (compare_aux(tokens->content, "unset") == 0)
		return (ft_unset(&tokens));
	else if (compare_aux(tokens->content, "pwd") == 0)
		return (ft_pwd(&tokens));
	return (tokens->next);
}

t_token	*exec(t_token *tokens, t_env *envs)
{
	if (!tokens)
		return (NULL);
	if (count_pipes(tokens) > 0)
		return (handle_pipes(tokens, envs));
	if (there_is_redir(tokens))
		return (handle_redirects(&tokens));
	else if (is_biut(tokens))
		return (exec_biut(tokens));
	else
		return (exec_external(tokens, envs));
}
