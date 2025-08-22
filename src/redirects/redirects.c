/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:15:26 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/21 22:18:06 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	copy_aux(t_token *new, t_token *current,
	t_token *head, t_token *prev)
{
	if (!new || !current || !current->content)
		return (1);
	new->content = ft_strdup(current->content);
	if (!new->content)
	{
		free_tokens(head);
		return (1);
	}
	new->type = current->type;
	new->next = NULL;
	if (prev)
		prev->next = new;
	return (0);
}

static void	*biut(t_token *tokens)
{
	t_token	*current;
	t_token	*new;

	gg()->temp = copy_tokens(tokens);
	if (!gg()->temp)
		return (NULL);
	current = gg()->temp;
	new = built_aux(current);
	if (!new)
	{
		free_tokens(gg()->temp);
		return (NULL);
	}
	tokens = exec_biut(new);
	free_tokens(new);
	free_tokens(gg()->temp);
	return (NULL);
}

t_token	*built_external(t_token *tokens, t_env *envs)
{
	t_token	*current;

	if (is_biut(tokens))
		return (biut(tokens));
	else
	{
		gg()->temp = copy_tokens(tokens);
		if (!gg()->temp)
			return (NULL);
		current = gg()->temp;
		built_external_aux(current);
		exec_external(gg()->temp, envs);
		free_tokens(gg()->temp);
		if (tokens && tokens->next)
			return (tokens->next);
		return (NULL);
	}
}

void	handle_heredoc_sigint(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	free_pids_here();
	exit(130);
}

void	free_pids_here(void)
{
	free_tokens(gg()->token);
	free_envs(gg()->envs);
	free(gg()->temp_h);
	free(gg()->temp_file_h);
	clear_history();
	if (gg()->pipe_count > 1)
	{
		free_safe(gg()->pids);
		free_pipes_memory(gg()->pipes, gg()->pipe_count);
	}
}
