/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_aux3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pede-jes <pede-jes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:40:27 by pede-jes          #+#    #+#             */
/*   Updated: 2025/08/11 20:04:33 by pede-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*handle_pipes(t_token *tokens, t_env *envs)
{
	int		pipe_count;
	t_token	*result;

	if (!tokens)
		return (NULL);

	pipe_count = count_pipes(tokens);

	if (pipe_count == 0)
		return (handle_redirects(&tokens));
	else if (pipe_count == 1)
	{
		gg()->segments = split_by_pipes(tokens);
		result = exec_single_pipe(gg()->segments[0], gg()->segments[1], envs);
		free_tokens(gg()->segments[0]);
		free_tokens(gg()->segments[1]);
		free_safe(gg()->segments);
		return (result);
	}
	else
		return (exec_multiple_pipes(tokens, envs));
}
t_token	*exec_multiple_pipes(t_token *tokens, t_env *envs)
{
	gg()->pipe_count = count_pipes(tokens);
	if (gg()->pipe_count == 0)
		return (handle_redirects(&tokens));
	gg()->segments = split_by_pipes(tokens);
	if (!gg()->segments)
		return (NULL);
	gg()->pipes = malloc(sizeof(int *) * gg()->pipe_count);
	create_pipes(gg()->pipes, gg()->pipe_count);
	gg()->pids = malloc(sizeof(pid_t) * (gg()->pipe_count + 1));
	create_child_processes(gg()->segments, gg()->pipes, gg()->pids, envs);
	close_all_pipes(gg()->pipes, gg()->pipe_count);
	wait_all_processes(gg()->pids, gg()->pipe_count);
	free_pipes_memory(gg()->pipes, gg()->pipe_count);
	free(gg()->pids);
	free_segments_memory(gg()->segments);

	return (NULL);
}
t_token	**split_by_pipes(t_token *tokens)
{
	int		pipe_count;
	t_token	**segments;
	t_token	*current;
	t_token	*segment_start;
	int	i;

	pipe_count = count_pipes(tokens);
	current = tokens;
	segment_start = tokens;
	i = 0;
	segments = malloc(sizeof(t_token *) * (pipe_count + 2));
	if (!segments)
		return (NULL);
	while (current)
	{
		if (current->type == PIPE)
		{
			segments[i++] = copy_until_pipe(segment_start, current);
			segment_start = current->next;
		}
		current = current->next;
	}
	segments[i] = copy_until_pipe(segment_start, NULL);
	segments[i + 1] = NULL;
	return (segments);
}
