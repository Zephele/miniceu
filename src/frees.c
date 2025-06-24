/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:51:13 by ratanaka          #+#    #+#             */
/*   Updated: 2025/06/23 19:26:18 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_global	*gg(void)
{
	static t_global	global;

	return (&global);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->content);
		free(tmp);
	}
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

int	is_empty(char *temp, char *content)
{		
	if (!temp)
	{
		free(content);
		return (1);
	}
	return (0);
}

int	is_empty_token(char *temp, t_token *token)
{		
	if (!temp)
	{
		free(token);
		return (1);
	}
	return (0);
}
