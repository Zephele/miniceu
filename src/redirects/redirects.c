/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:15:26 by ratanaka          #+#    #+#             */
/*   Updated: 2025/07/31 15:36:06 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_file_reddir(int type, const char *filename)
{
	int		fd;
	char	*temp;

	fd = -1;
	temp = ft_strdup(filename);
	temp = no_quotes(temp);
	if (type == 3)
		fd = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == 4)
		fd = open(temp, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Open file error");
		free (temp);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Open file error");
		close(fd);
		free (temp);
		return (-1);
	}
	close(fd);
	free (temp);
	return (0);
}

static t_token	*copy_tokens(t_token *tokens)
{
	t_token	*head;
	t_token	*prev;
	t_token	*new_token;

	head = NULL;
	prev = NULL;
	while (tokens)
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
		{
			free_tokens(head);
			return (NULL);
		}
		new_token->content = ft_strdup(tokens->content);
		new_token->type = tokens->type;
		new_token->next = NULL;
		if (!head)
			head = new_token;
		if (prev)
			prev->next = new_token;
		prev = new_token;
		tokens = tokens->next;
	}
	return (head);
}

static void	built_external_aux(t_token *current)
{
	while (current->content
		&& current->type != PIPE
		&& current->type != REDIR_IN
		&& current->type != REDIR_OUT
		&& current->type != REDIR_APPEND
		&& current->type != HEREDOC
		&& current->type != ENV)
		current = current->next;
	while (current)
	{
		if (current->content)
		{
			free (current->content);
			current->content = NULL;
			current = current->next;
		}
	}
}

static void	built_aux(t_token *current)
{
	t_token	*pass;
	int		i;

	pass = current;
	i = 0;
	while (current)
	{
		while (current->content
			&& current->type != REDIR_IN
			&& current->type != REDIR_OUT
			&& current->type != REDIR_APPEND
			&& current->type != HEREDOC
			&& current->type != ENV)
			current = current->next;
		pass = current;
		while (current)
		{
			if (current->type == 0 || current->type == 1)
			{
				free (pass->content);
				pass->content = NULL;
				pass->content = ft_strdup(current->content);
				pass->type = current->type;
				pass = pass->next;
				current = current->next;
			}
			else if (current && current->next && current->next->next)
			{
				i += 2;
				current = current->next->next;
				if (current->type != 0 && current->type != 1)
				{
					if (current && current->next && current->next->next)
					{
						current = current->next->next;
						i += 2;
					}
				}
			}
			else
				current = current->next;
		}
	}
	while (pass)
	{
		if (pass->content)
		{
			free (pass->content);
			pass->content = NULL;
			pass->type = 8;
			pass = NULL;
			current = NULL;
		}
	}
}

				// else
				// {
				// 	free (pass->content);
				// 	pass->content = NULL;
				// 	pass->content = ft_strdup(current->content);
				// 	pass->type = current->type;
				// 	pass = pass->next;
				// 	current = current->next;
				// 	i--;
				// }

t_token	*built_external(t_token *tokens, t_env *envs)
{
	t_token	*current;
	t_token	*temp;

	if (is_biut(tokens))
	{
		temp = copy_tokens(tokens);
		current = temp;
		built_aux(current);
		tokens = exec_biut(temp);
		free_tokens (temp);
		write (1, "\n", 1);
		return (NULL);
	}
	else
	{
		temp = copy_tokens(tokens);
		current = temp;
		built_external_aux(current);
 		exec_external(temp, envs);
		free_tokens (temp);
		return (tokens->next);
	}
}



// static void	built_aux(t_token *current)
// {
// 	t_token	*pass;

// 	while (current->content
// 		&& current->type != PIPE
// 		&& current->type != REDIR_IN
// 		&& current->type != REDIR_OUT
// 		&& current->type != REDIR_APPEND
// 		&& current->type != HEREDOC
// 		&& current->type != ENV)
// 		current = current->next;
// 	pass = current;
// 	if (current && current->next && current->next->next)
// 		current = current->next->next;
// 	else
// 		return ;
// 	while (current)
// 	{
// 		free (pass->content);
// 		pass->content = NULL;
// 		pass->content = ft_strdup(current->content);
// 		pass->type = current->type;
// 		pass = pass->next;
// 		current = current->next;
// 	}
// 	if (!current)
// 	{
// 		current = pass;
// 		while (pass)
// 		{
// 			if (pass->content)
// 			{
// 				free (pass->content);
// 				pass->content = NULL;
// 				pass->type = 8;
// 				pass = NULL;
// 				current = NULL;
// 			}
// 		}
// 	}
// }










// t_token	*handle_redirects(t_token **tokens)
// {
// 	int		saved_stdout;
// 	t_token	*current;

// 	saved_stdout = dup(STDOUT_FILENO);
// 	current = *tokens;
// 	while (current && current->type != PIPE)
// 	{
// 		if (current->type == 3 || current->type == 4)
// 		{
// 			if (open_file_reddir(current->type, current->next->content) == -1)
// 			{
// 				dup2(saved_stdout, STDOUT_FILENO);
// 				close(saved_stdout);
// 				return (NULL);
// 			}
// 		}
// 		current = current->next;
// 	}
// 	current = built_external(*tokens, gg()->envs);
// 	while (current && current->type != PIPE)
// 		current = current->next;
// 	dup2(saved_stdout, STDOUT_FILENO);
// 	close(saved_stdout);
// 	return (current);
// }

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