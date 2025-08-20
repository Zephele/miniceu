/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:45:39 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/20 16:38:47 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>

char	*gen_tmp_file(int index)
{
	char	*base;
	char	*num;
	char	*filename;

	base = "/tmp/minishell_heredoc_";
	num = ft_itoa(index);
	filename = ft_strjoin(base, num);
	free_safe(num);
	return (filename);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

int	ft_hmheres(t_token *current)
{
	int	heres;

	heres = 0;
	while (current)
	{
		if (current->type == 5)
			heres++;
		if (current->next)
			current = current->next;
		else
			break ;
	}
	return (heres);
}

void	*error_redir(int saved_stdout, int saved_stdin, t_list **lst, int i)
{
	if (i == 1)
	{
		ft_lstclear(lst, free);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		gg()->last_status = 1;
		return (NULL);
	}
	if (i == 2)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	return ("o");
}

t_token	*current_aux(t_token *current)
{
	while (current)
	{
		if (current->next && (current->next->content[0] == '.'
				&& current->next->content[1] == '/'))
				current = current->next;
		else if (current->next && (current->next->content[0] == '\''
				|| current->next->content[0] == '\"'))
		{
			if (current->next && (current->next->content[1] == '.'
					&& current->next->content[2] == '/'))
				current = current->next;
			else
				break ;
		}
		else
			break ;
	}
	return (current);
}
