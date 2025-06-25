/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:42:56 by ratanaka          #+#    #+#             */
/*   Updated: 2025/06/25 16:14:04 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*ft_pwd(t_token **token)
{
	char	*cwd;

	if (token && ft_strncmp((*token)->content, "pwd", 3) == 0)
	{
		*token = (*token)->next;
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			ft_putstr_fd(cwd, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			free (cwd);
		}
	}
	return (*token);
}
