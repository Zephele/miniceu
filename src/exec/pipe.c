/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:52:52 by ratanaka          #+#    #+#             */
/*   Updated: 2025/07/30 11:45:15 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/wait.h>

static void	exec_left_command(t_token *left_tokens, int pipefd[2], t_env *envs)
{
	dup2(pipefd[1], STDOUT_FILENO); // Redireciona stdout para o pipe
	close(pipefd[0]);				// Fecha o lado de leitura
	close(pipefd[1]);				// Fecha o lado de escrita após dup2
	exec(left_tokens, envs);		// Executa o comando à esquerda
	exit(1);						// Sai em caso de falha
}

static void	exec_right_command(t_token *right_tokens, int pipefd[2], t_env *envs)
{
	dup2(pipefd[0], STDIN_FILENO); // Redireciona stdin para o pipe
	close(pipefd[0]);			   // Fecha o lado de leitura após dup2
	close(pipefd[1]);			   // Fecha o lado de escrita
	exec(right_tokens, envs);	   // Executa o comando à direita
	exit(1);					   // Sai em caso de falha
}

t_token	*exec_pipe(t_token *left_tokens, t_token *right_tokens, t_env *envs)
{
	int	pipefd[2];
	pid_t	pid_left, pid_right;

	// Cria o pipe
	if (pipe(pipefd) == -1)
	{
		perror("minishell: pipe");
		gg()->last_status = 1;
		return NULL;
	}

	// Fork para o comando à esquerda
	pid_left = fork();
	if (pid_left == 0)
	{
		exec_left_command(left_tokens, pipefd, envs);
	}
	else if (pid_left < 0)
	{
		perror("minishell: fork");
		gg()->last_status = 1;
		return NULL;
	}

	// Fork para o comando à direita
	pid_right = fork();
	if (pid_right == 0)
	{
		exec_right_command(right_tokens, pipefd, envs);
	}
	else if (pid_right < 0)
	{
		perror("minishell: fork");
		gg()->last_status = 1;
		return NULL;
	}

	// Processo pai fecha os descritores e espera os filhos
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &gg()->last_status, 0);
	gg()->last_status = WEXITSTATUS(gg()->last_status); // Status do comando à direita

	// Retorna o próximo token após o pipe
	return right_tokens ? right_tokens->next : NULL;
}