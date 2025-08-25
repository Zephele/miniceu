/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_segment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:15:37 by pede-jes          #+#    #+#             */
/*   Updated: 2025/08/25 17:10:34 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static pid_t	create_process(t_token **segments,
	int **pipes, int heredoc_fd, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (i > 0)
			close(pipes[i - 1][1]);
		if (i < gg()->pipe_count)
			close(pipes[i][0]);
		if (heredoc_fd != -1)
		{
			dup2(heredoc_fd, STDIN_FILENO);
			close(heredoc_fd);
			free_safe(gg()->heredoc_file);
		}
		else if (i > 0)
			dup2(pipes[i - 1][0], STDIN_FILENO);
		if (i < gg()->pipe_count)
			dup2(pipes[i][1], STDOUT_FILENO);
		close_all_pipes(pipes, gg()->pipe_count);
		execute_child_process(segments, pipes, gg()->pipe_count, i);
		exit(gg()->last_status);
	}
	return (pid);
}

static int	heredoc_fds(t_token *heredoc_token, int i)
{
	int		heredoc_fd;
	char	*heredoc_file;

	heredoc_file = gg()->heredoc_file;
	if (heredoc_token && heredoc_token->next)
	{
		heredoc_file = ft_read_heredoc(heredoc_token->next->content, i, NULL);
		if (!heredoc_file)
		{
			perror("heredoc");
			exit(1);
		}
		gg()->heredoc_file = heredoc_file;
		heredoc_fd = open(gg()->heredoc_file, O_RDONLY);
		if (heredoc_fd == -1)
		{
			free_safe(gg()->heredoc_file);
			gg()->heredoc_file = NULL;
			exit(1);
		}
	}
	else
		heredoc_fd = -1;
	return (heredoc_fd);
}

void	create_child_processes(t_token **segments, int **pipes, pid_t *pids)
{
	int		pipe_count;
	t_token	*heredoc_token;
	int		i;
	int		heredoc_fd;

	pipe_count = gg()->pipe_count;
	i = 0;
	while (i <= pipe_count)
	{
		heredoc_token = find_heredoc_token(segments[i]);
		heredoc_fd = heredoc_fds(heredoc_token, i);
		pids[i] = create_process(segments, pipes, heredoc_fd, i);
		if (heredoc_fd != -1)
		{
			close(heredoc_fd);
			free_safe(gg()->heredoc_file);
			gg()->heredoc_file = NULL;
		}
		if (i > 0)
			close(pipes[i - 1][0]);
		if (i < pipe_count)
			close(pipes[i][1]);
		i++;
	}
}
