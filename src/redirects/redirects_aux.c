/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:36:08 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/05 19:51:49 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_a1(t_token *current, t_token *pass, int i)
{
	if (i == 1)
	{
		free (pass->content);
		pass->content = NULL;
		pass->content = ft_strdup(current->content);
		pass->type = current->type;
	}
	if (i == 2)
	{
		free (pass->content);
		pass->content = NULL;
		pass->type = 8;
		pass = NULL;
		current = NULL;
	}
}

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
