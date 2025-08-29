/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_aux2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:32:02 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/29 17:50:02 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	allocate_next(t_token **new_token, t_token **head)
{
	(*new_token)->next = malloc(sizeof(t_token));
	if (!(*new_token)->next)
	{
		free_tokens(*head);
		return ;
	}
	*new_token = (*new_token)->next;
	(*new_token)->content = NULL;
	(*new_token)->type = 0;
	(*new_token)->next = NULL;
}

static t_token	*process_while(t_token *current, t_token **new_token,
					t_token **head, t_token **prev)
{
	if (copy_aux(*new_token, current, *head, *prev))
	{
		free_tokens(*head);
		return (NULL);
	}
	*prev = *new_token;
	if (current->next && (current->next->type == 0
			|| current->next->type == 1))
		allocate_next(new_token, head);
	current = current->next;
	return (current);
}

static void	process_tokens(t_token *current, t_token **head,
	t_token **new_token, t_token **prev)
{
	while (current && current->type != 8)
	{
		while (current && (current->type == 0 || current->type == 1))
			current = process_while(current, new_token, head, prev);
		while (current && current->type != 8)
		{
			if ((current->type == 0 || current->type == 1) && current->content)
				current = process_while(current, new_token, head, prev);
			else if (current && current->next && current->next->next)
			{
				current = b_a2(current);
				allocate_next(new_token, head);
				*prev = *new_token;
			}
			else if (current && current->next && !current->next->next)
				current = current->next->next;
			else
				current = current->next;
		}
	}
	(*prev)->next = NULL;
}

t_token	*built_aux(t_token *current)
{
	t_token	*head;
	t_token	*prev;
	t_token	*new_token;

	if (!current)
		return (NULL);
	head = malloc(sizeof(t_token));
	if (!head)
		return (NULL);
	new_token = head;
	new_token->content = NULL;
	new_token->type = 0;
	new_token->next = NULL;
	prev = NULL;
	process_tokens(current, &head, &new_token, &prev);
	return (head);
}

void	handle_heredoc_sigint(int signal)
{
	int	i;

	i = 2;
	(void)signal;
	write(1, "\n", 1);
	free_pids_here();
	free_safe(gg()->deli_noquot);
	while (i++ < 1000)
		close(i);
	if (gg()->theres_pipe == 1)
	{
		clear_history();
		free_safe(gg()->pids);
		free_segments_memory(gg()->segments);
		free_safe(gg()->input_f);
	}
	if (gg()->theres_pipe > 1)
		free_segments_memory(gg()->segments);
	exit(130);
}
