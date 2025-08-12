/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:15:26 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/11 19:37:01 by ratanaka         ###   ########.fr       */
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

void	copy_aux(t_token *new, t_token *current, t_token *head, t_token *prev)
{
	if (!new || !current || !current->content)
		return ;
	new->content = ft_strdup(current->content);
	if (!new->content)
	{
		free_tokens(head);
		return ;
	}
	new->type = current->type;
	new->next = NULL;
	if (prev)
		prev->next = new;
}

static int	copy_aux_2(t_token *new_token, t_token *current, t_token *head, t_token *prev)
{
	copy_aux(new_token, current, head, prev);
	return (0);
}

static t_token	*built_aux(t_token *current)
{
	t_token	*pass;
	t_token	*head;
	t_token	*prev;
	t_token	*new_token;

	if (!current)
		return (NULL);

	// Aloca o primeiro token da nova lista
	head = malloc(sizeof(t_token));
	if (!head)
		return (NULL);
	new_token = head;
	new_token->content = NULL;
	new_token->type = 0;
	new_token->next = NULL;

	pass = current;
	prev = NULL;

	while (current && current->type != 8)
	{
		while (current && (current->type == 0 || current->type == 1))
		{
			if (copy_aux_2(new_token, current, head, prev))
			{
				free_tokens(head);
				return (NULL);
			}
			prev = new_token;
			// Aloca o próximo token apenas se necessário e vincula corretamente
			if (current->next && (current->next->type == 0 || current->next->type == 1))
			{
				new_token->next = malloc(sizeof(t_token));
				if (!new_token->next)
				{
					free_tokens(head);
					return (NULL);
				}
				new_token = new_token->next;
				new_token->content = NULL;
				new_token->type = 0;
				new_token->next = NULL;
			}
			current = current->next;
		}
		while (current && current->type != 8)
		{
			if ((current->type == 0 || current->type == 1) && current->content)
			{
				if (copy_aux_2(new_token, current, head, prev))
				{
					free_tokens(head);
					return (NULL);
				}
				prev = new_token;
				// Aloca o próximo token apenas se necessário e vincula corretamente
				if (current->next && (current->next->type == 0 || current->next->type == 1))
				{
					new_token->next = malloc(sizeof(t_token));
					if (!new_token->next)
					{
						free_tokens(head);
						return (NULL);
					}
					new_token = new_token->next;
					new_token->content = NULL;
					new_token->type = 0;
					new_token->next = NULL;
				}
				current = current->next;
			}
			else if (current && current->next && current->next->next)
			{
				current = b_a2(current);
				new_token->next = malloc(sizeof(t_token));
				if (!new_token->next)
				{
					free_tokens(head);
					return (NULL);
				}
				new_token = new_token->next;
				new_token->content = NULL;
				new_token->type = 0;
				new_token->next = NULL;
				prev = new_token;
			}
			else if (current && current->next && !current->next->next)
				current = current->next->next;
			else
				current = current->next;
		}
	}
	prev->next = NULL;
	return (head);
}

t_token	*built_external(t_token *tokens, t_env *envs)
{
	t_token	*current;
	t_token	*new;

	if (is_biut(tokens))
	{
		gg()->temp = copy_tokens(tokens);
		if (!gg()->temp)
			return (NULL);
		current = gg()->temp;
		new = built_aux(current);
		if (!new)
		{
			free_tokens(gg()->temp);
			return (NULL);
		}
		tokens = exec_biut(new);
		free_tokens(new);
		free_tokens(gg()->temp);
		return (NULL);
	}
	else
	{
		gg()->temp = copy_tokens(tokens);
		if (!gg()->temp)
			return (NULL);
		current = gg()->temp;
		built_external_aux(current);
		exec_external(gg()->temp, envs);
		free_tokens(gg()->temp);
		if (tokens && tokens->next)
			return (tokens->next);
		return (NULL);
	}
}

// void	copy_aux(t_token *new, t_token *current,
// 		t_token *head, t_token *prev)
// {
// 	new->content = ft_strdup(current->content);
// 	new->type = current->type;
// 	new->next = NULL;
// 	if (!head)
// 		head = new;
// 	if (prev)
// 		prev->next = new;
// 	prev = new;
// 	current = current->next;
// }

// static t_token	*built_aux(t_token *current)
// {
// 	t_token	*pass;
// 	t_token	*head;
// 	t_token	*prev;

// 	pass = current;
// 	head = NULL;
// 	prev = NULL;
// 	gg()->new = malloc(sizeof(t_token));
// 	if (!gg()->new)
// 	{
// 		free_tokens(head);
// 		return (NULL);
// 	}
// 	while (current && current->type != 8)
// 	{
// 		while (current->type == 0 || current->type == 1)
// 			current = current->next;
// 		while (current && current->type != 8)
// 		{
// 			if ((current->type == 0 || current->type == 1) && current->content)
// 			{
// 				copy_aux(gg()->new, current, head, prev);
// 				current = current->next;
// 			}
// 			else if (current && current->next && current->next->next)
// 				current = b_a2(current);
// 			else if (current && current->next && !current->next->next)
// 				current = current->next->next;
// 			else
// 				current = current->next;
// 		}
// 	}
// 	free_tokens(current);
// 	return (head);
// }

// t_token	*built_external(t_token *tokens, t_env *envs)
// {
// 	t_token	*current;
// 	t_token	*new;

// 	if (is_biut(tokens))
// 	{
// 		gg()->temp = copy_tokens(tokens);
// 		current = gg()->temp;
// 		free_tokens(gg()->new_token);
// 		new = built_aux(current);
// 		if (!new)
// 			return (NULL);
// 		tokens = exec_biut(new);
// 		free_tokens(new);
// 		write (1, "\n", 1);
// 		return (NULL);
// 	}
// 	else
// 	{
// 		gg()->temp = copy_tokens(tokens);
// 		current = gg()->temp;
// 		built_external_aux(current);
// 		exec_external(gg()->temp, envs);
// 		free_tokens (gg()->temp);
// 		return (tokens->next);
// 	}
// }
