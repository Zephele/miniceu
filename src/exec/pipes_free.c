/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:00:25 by pede-jes          #+#    #+#             */
/*   Updated: 2025/08/12 15:24:08 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_pipes_memory(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
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

void	free_pipe_2(void)
{
	free_tokens(gg()->token);
	free_envs(gg()->envs);
	clear_history();
	free_pipes_memory(gg()->pipes, gg()->pipe_count);
	free(gg()->pids);
	free_segments_memory(gg()->segments);
}
