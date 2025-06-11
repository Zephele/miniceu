/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:23:16 by ratanaka          #+#    #+#             */
/*   Updated: 2025/06/11 14:51:07 by ratanaka         ###   ########.fr       */
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
			return (NULL);
		}
	}
	else
		path = token->content;
	if (token && token->next->content != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (NULL);
	}
	else
		return (path);
}

void	ft_cd(t_token *token)
{
	char	*path;

	if (token && ft_strncmp(token->content, "cd", 2) == 0)
	{
		token = token->next;
		path = valid_cmd(token);
		if (!path)
			return ;
		if (chdir(path) != 0)
			perror ("cd");
	}
}
