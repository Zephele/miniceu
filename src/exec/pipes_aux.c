/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 19:18:22 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/22 19:22:57 by ratanaka         ###   ########.fr       */
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
