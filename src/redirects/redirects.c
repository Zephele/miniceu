/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:15:26 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/08 21:35:54 by ratanaka         ###   ########.fr       */
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
		return (exit_file(fd, temp, 1));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (exit_file(fd, temp, 2));
	close(fd);
	free (temp);
	return (0);
}

t_token	*copy_tokens(t_token *tokens)
{
	t_token	*head;
	t_token	*prev;

	head = NULL;
	prev = NULL;
	while (tokens)
	{
		gg()->new_token = malloc(sizeof(t_token));
		if (!gg()->new_token)
		{
			free_tokens(head);
			return (NULL);
		}
		gg()->new_token->content = ft_strdup(tokens->content);
		gg()->new_token->type = tokens->type;
		gg()->new_token->next = NULL;
		if (!head)
			head = gg()->new_token;
		if (prev)
			prev->next = gg()->new_token;
		prev = gg()->new_token;
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

	pass = current;
	while (current && current->type != 8)
	{
		while (current->type == 0 || current->type == 1)
			current = current->next;
		pass = current;
		while (current && current->type != 8)
		{
			if (current->type == 0 || current->type == 1)
			{
				b_a1(current, pass, 1);
				pass = pass->next;
				current = current->next;
			}
			else if (current && current->next && current->next->next)
				current = b_a2(current);
			else if (current && current->next && !current->next->next)
			{
				b_a3(current);
				break ;
			}
			else
				current = current->next;
		}
	}
	if (pass->content)
		b_a1(current, pass, 2);
}

t_token	*built_external(t_token *tokens, t_env *envs)
{
	t_token	*current;

	if (is_biut(tokens))
	{
		gg()->temp = copy_tokens(tokens);
		current = gg()->temp;
		built_aux(current);
		tokens = exec_biut(gg()->temp);
		free_tokens(gg()->new_token);
		free_tokens(gg()->temp);
		write (1, "\n", 1);
		return (NULL);
	}
	else
	{
		gg()->temp = copy_tokens(tokens);
		current = gg()->temp;
		built_external_aux(current);
		exec_external(gg()->temp, envs);
		free_tokens (gg()->temp);
		return (tokens->next);
	}
}
