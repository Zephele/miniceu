/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:15:26 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/28 14:09:26 by ratanaka         ###   ########.fr       */
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

static t_token	*is_biut_in(t_token *tokens)
{
	while (tokens)
	{
		if (!tokens || !tokens->content)
			return (NULL);
		if (compare_aux(tokens->content, "echo") == 0
			|| compare_aux(tokens->content, "cd") == 0
			|| compare_aux(tokens->content, "exit") == 0
			|| compare_aux(tokens->content, "env") == 0
			|| compare_aux(tokens->content, "unset") == 0
			|| compare_aux(tokens->content, "export") == 0
			|| compare_aux(tokens->content, "pwd") == 0)
			return (tokens);
		else
		{
			if (tokens && tokens->next)
				tokens = tokens->next;
			else
				return (NULL);
		}
	}
	return (NULL);
}

t_token	*built_external(t_token *tokens, t_env *envs)
{
	t_token	*current;
	t_token	*biut_t;

	biut_t = tokens;
	biut_t = is_biut_in(tokens);
	if (biut_t)
		return (biut(biut_t));
	else
	{
		gg()->temp = copy_tokens(tokens);
		if (!gg()->temp)
			return (NULL);
		current = gg()->temp;
		current = built_external_aux1(current);
		exec_external(current, envs);
		free_tokens(gg()->temp);
		if (tokens && tokens->next)
			return (tokens->next);
		return (NULL);
	}
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
