/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:32:46 by pede-jes          #+#    #+#             */
/*   Updated: 2025/08/14 18:07:08 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*copy_until_pipe(t_token *start, t_token *end)
{
	t_token	*new_head;
	t_token	*new_current;
	t_token	*current;
	t_token	*new_token;

	new_head = NULL;
	new_current = NULL;
	current = start;
	while (current && current != end)
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (NULL);
		new_token->content = ft_strdup(current->content);
		new_token->type = current->type;
		new_token->next = NULL;
		if (!new_head)
			new_head = new_token;
		else
			new_current->next = new_token;
		new_current = new_token;
		current = current->next;
	}
	return (new_head);
}

void	create_pipes(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			return ;
		}
		i++;
	}
}

void	close_all_pipes(int **pipes, int pipe_count)
{
	int	j;

	j = 0;
	while (j < pipe_count)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	setup_child_process(int **pipes, int pipe_count, int i)
{
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < pipe_count)
		dup2(pipes[i][1], STDOUT_FILENO);
	close_all_pipes(pipes, pipe_count);
	free_pipes_memory(gg()->pipes, gg()->pipe_count);
}

void	wait_all_processes(pid_t *pids, int pipe_count)
{
	int	status;
	int	i;

	i = 0;
	while (i <= pipe_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == pipe_count)
			gg()->last_status = WEXITSTATUS(status);
		i++;
	}
}
