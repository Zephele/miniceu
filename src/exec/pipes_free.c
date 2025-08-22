/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:00:25 by pede-jes          #+#    #+#             */
/*   Updated: 2025/08/22 15:59:19 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_pipes_memory(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		free_safe(pipes[i]);
		i++;
	}
	free_safe(pipes);
}

void	free_segments_memory(t_token **segments)
{
	int	i;

	i = 0;
	while (segments[i])
	{
		free_tokens(segments[i]);
		i++;
	}
	free(segments);
}

void	free_pipe(void)
{
	free_tokens(gg()->token);
	free_envs(gg()->envs);
	clear_history();
	free_safe(gg()->input_f);
	if (gg()->segments)
	{
		if (gg()->segments[0] && gg()->segments[0]->type != 8)
			free_tokens(gg()->segments[0]);
		gg()->segments[0] = NULL;
		if (gg()->segments[1] && gg()->segments[1]->type != 8)
			free_tokens(gg()->segments[1]);
		gg()->segments[1] = NULL;
		free_safe(gg()->segments);
		gg()->segments = NULL;
	}
	else
		return ;
}

void	free_pipe_2(void)
{
	free_tokens(gg()->token);
	free_envs(gg()->envs);
	clear_history();
	free(gg()->pids);
	free_segments_memory(gg()->segments);
	free_safe(gg()->input_f);
}
