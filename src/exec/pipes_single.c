/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_single.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:15:42 by pede-jes          #+#    #+#             */
/*   Updated: 2025/08/14 17:36:45 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static pid_t	create_left_process(t_token *left_tokens,
// 	int pipefd[2], t_env *envs)
// {
// 	pid_t	pid1;

// 	pid1 = fork();
// 	if (pid1 == 0)
// 	{
// 		close(pipefd[0]);
// 		execute_pipe_segment(left_tokens, STDIN_FILENO, pipefd[1], envs);
// 	}
// 	return (pid1);
// }

// static pid_t	create_right_process(t_token *right_tokens,
// 	int pipefd[2], t_env *envs)
// {
// 	pid_t	pid2;

// 	pid2 = fork();
// 	if (pid2 == 0)
// 	{
// 		close(pipefd[1]);
// 		execute_pipe_segment(right_tokens, pipefd[0], STDOUT_FILENO, envs);
// 	}
// 	return (pid2);
// }

static void	wait_and_set_status(pid_t pid1, pid_t pid2)
{
	int	status;

	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	gg()->last_status = WEXITSTATUS(status);
}

// t_token	*exec_single_pipe(t_token *left_tokens,
// 	t_token *right_tokens, t_env *envs)
// {
// 	int		pipefd[2];
// 	pid_t	pid1;
// 	pid_t	pid2;

// 	if (pipe(pipefd) == -1)
// 	{
// 		perror("pipe");
// 		return (NULL);
// 	}
// 	pid1 = create_left_process(left_tokens, pipefd, envs);
// 	pid2 = create_right_process(right_tokens, pipefd, envs);
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	wait_and_set_status(pid1, pid2);
// 	return (NULL);
// }


// Função auxiliar para encontrar o token de heredoc
t_token	*find_heredoc_token(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == HEREDOC)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

t_token	*exec_single_pipe(t_token *left_tokens, t_token *right_tokens, t_env *envs)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	gg()->heredoc_file = NULL;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (NULL);
	}
	t_token *heredoc_token = find_heredoc_token(left_tokens);
	if (heredoc_token)
	{
		gg()->heredoc_file = ft_read_heredoc(heredoc_token->next->content, 0, NULL);
		if (!gg()->heredoc_file)
			return (NULL);
	}
	pid1 = fork();
	if (pid1 == 0)
	{
		close(pipefd[0]);
		if (gg()->heredoc_file)
		{
			int fd = open(gg()->heredoc_file, O_RDONLY);
			if (fd >= 0)
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
		}
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		if (gg()->heredoc_file)
			free_safe(gg()->heredoc_file);
		execute_pipe_segment(left_tokens, STDIN_FILENO, STDOUT_FILENO, envs);
		exit(gg()->last_status);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		if (gg()->heredoc_file)
			free_safe(gg()->heredoc_file);
		execute_pipe_segment(right_tokens, STDIN_FILENO, STDOUT_FILENO, envs);
		exit(gg()->last_status);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	if (gg()->heredoc_file)
		free(gg()->heredoc_file);
	wait_and_set_status(pid1, pid2);
	return (NULL);
}
