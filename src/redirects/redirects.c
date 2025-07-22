/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:15:26 by ratanaka          #+#    #+#             */
/*   Updated: 2025/07/22 20:23:55 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_file_reddir(int type, const char *filename)
{
	int	fd;

	fd = -1;
	if (type == 3)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == 4)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Open file error");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Open file error");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static t_token	*built_external(t_token *tokens, t_env *envs)
{
	if (is_biut(tokens))
		return (exec_biut(tokens));
	else
	{
		exec_external(tokens, envs);
		return (tokens->next);
	}
}

t_token	*handle_redirects(t_token **tokens)
{
	int		saved_stdout;
	t_token	*current;

	saved_stdout = dup(STDOUT_FILENO);
	current = *tokens;

	while (current && current->type != PIPE)
	{
		if (current->type == 3 || current->type == 4)
		{
			if (open_file_reddir(current->type, current->next->content) == -1)
			{
				dup2(saved_stdout, STDOUT_FILENO);
				close(saved_stdout);
				return (NULL);
			}
		}
		current = current->next;
	}
	current = built_external(*tokens, gg()->envs);
	while (current && current->type != PIPE)
		current = current->next;
	write (1, "\n", 1);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	return (current);
}

// >
// open flag O_WRONLY | O_CREAT | O_TRUNC.
// Permissões padrão para o arquivo criado (ex.: 0644).
// O FD retornado por open substitui o stdout usando dup2.

//----------------------------

// >>
// open flag O_WRONLY | O_CREAT | O_APPEND.
// Permissões padrão (ex.: 0644).
// Substitui o stdout com dup2.

//----------------------------

//Exemplo: 
//int fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

//Criar uma funcao qeu pega o primeiro argumento e passa para um arquivo
// ex: echo > oi.txt

//se achar um '>' ou '>>' nos tokens muda a saida do exec?


//{dup}
// int fd = open("arquivo.txt", O_WRONLY); // Abre o arquivo e retorna fd (ex.: 3)
// int novo_fd = dup(fd);                  // Cria uma cópia (ex.: 4)
// write(novo_fd, "oi", 2);                // Escreve "oi" no arquivo
// close(novo_fd);                         // Fecha a cópia
// close(fd);                              // Fecha o original

//{dup2}
// int fd = open("saida.txt", O_WRONLY | O_CREAT, 0644); // Abre o arquivo
// dup2(fd, 1);                                  // Faz o stdout (1) apontar para o arquivo
// printf("ola");                                // Escreve "ola" no arquivo, não no terminal
// close(fd);                                    // Fecha o descritor