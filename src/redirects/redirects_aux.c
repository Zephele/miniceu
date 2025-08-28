/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:36:08 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/28 14:30:55 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*b_a2(t_token *current)
{
	current = current->next->next;
	if (current->type != 0 && current->type != 1)
	{
		if (current && current->next && current->next->next)
			current = current->next->next;
	}
	return (current);
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

int	exit_file(int fd, char *temp, int i)
{
	if (i == 1)
	{
		perror("Open file error");
		free_safe (temp);
	}
	else if (i == 2)
	{
		perror("Open file error");
		close(fd);
		free_safe (temp);
	}
	return (-1);
}

t_token	*built_external_aux1(t_token *current)
{
	t_token	*now;
	int		i;

	i = 0;
	now = current;
	while (current)
	{
		if (current->content && (current->type == 0
				|| current->type == 1 || current->type == 7))
		{
			if (i == 0)
				now = current;
			i++;
			current = current->next;
		}
		else
			current = free_reddirs(current);
	}
	return (now);
}
