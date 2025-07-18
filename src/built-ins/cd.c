/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:23:16 by ratanaka          #+#    #+#             */
/*   Updated: 2025/07/18 16:58:00 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*valid_cmd(t_token *token)
{
	char	*path;

	path = getenv("HOME");
	if (!token || ft_strncmp(token->content, "~\0", 2) == 0)
	{
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			gg()->last_status = 1;
			return (NULL);
		}
	}
	else
	{
		if (token->content[0] == '$')
		{
			path = expand_env_vars(token->content);
			token->content = ft_strdup("");
		}
		else
			path = token->content;
	}
	if (token && token->next != NULL && token->next->content != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		gg()->last_status = 1;
		return (NULL);
	}
	else
		return (path);
}

t_token	*ft_cd(t_token **token)
{
	char	*path;

	if (token && ft_strncmp((*token)->content, "cd", 2) == 0)
	{
		*token = (*token)->next;
		path = valid_cmd(*token);
		if (!path)
			return (NULL);
		if (chdir(path) != 0)
		{
			perror ("cd");
			*token = (*token)->next;
			gg()->last_status = 1;
			return (*token);
		}
	}
	*token = (*token)->next;
	gg()->last_status = 0;
	return (*token);
}
