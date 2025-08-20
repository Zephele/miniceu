/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_segment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:15:37 by pede-jes          #+#    #+#             */
/*   Updated: 2025/08/20 15:35:43 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	setup_pipe_redirections(int input_fd, int output_fd)
{
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
}

void	execute_pipe_segment(t_token *tokens, int input_fd,
	int output_fd, t_env *envs)
{
	setup_pipe_redirections(input_fd, output_fd);
	if (there_is_redir(tokens))
	{
		handle_redirects(&tokens);
		free_pipe();
		gg()->new_token = NULL;
		exit(gg()->last_status);
	}
	else if (is_biut(tokens))
	{
		exec_biut(tokens);
		free_pipe();
		exit(gg()->last_status);
	}
	else
	{
		exec_external(tokens, envs);
		free_pipe();
		exit(gg()->last_status);
	}
}

static void	execute_child_process(t_token **segments, int **pipes,
	int pipe_count, int i)
{
	setup_child_process(pipes, pipe_count, i);
	if (there_is_redir(segments[i]))
	{
		handle_redirects(&segments[i]);
		free_pipe_2();
		exit(gg()->last_status);
	}
	if (is_biut(segments[i]))
	{
		exec_biut(segments[i]);
		free_pipe_2();
		exit(gg()->last_status);
	}
	else
	{
		exec_external(segments[i], gg()->envs);
		free_pipe_2();
		exit(gg()->last_status);
	}
}

void	create_child_processes(t_token **segments,
			int **pipes, pid_t *pids)
{
	int	pipe_count;
	int	i;

	i = 0;
	pipe_count = 0;
	while (segments[pipe_count])
		pipe_count++;
	pipe_count--;
	while (i <= pipe_count)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			execute_child_process(segments, pipes, pipe_count, i);
		i++;
	}
}

int	count_pipes(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		if (current->type == PIPE)
			count++;
		current = current->next;
	}
	gg()->theres_pipe = count;
	return (count);
}
