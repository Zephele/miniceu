/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:42:56 by ratanaka          #+#    #+#             */
/*   Updated: 2025/07/18 15:32:57 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	verify_argum(t_token **token)
{
	int	count;

	count = 0;
	if ((!(*token)->next))
		return (count);
	if ((*token)->content)
	{
		while ((*token)->content[0] != PIPE
			&& (*token)->content[0] != REDIR_IN
			&& (*token)->content[0] != REDIR_OUT
			&& (*token)->content[0] != REDIR_APPEND
			&& (*token)->content[0] != HEREDOC
			&& (*token)->content[0] != ENV)
		{
			if ((*token)->next)
			{
				count++;
				*token = (*token)->next;
			}
			else
				break ;
		}
	}
	return (count);
}

t_token	*after_comand(t_token **token)
{
	int		count;

	count = 0;
	if ((*token)->next)
	{
		count = verify_argum(token);
		if (count)
			*token = (*token)->next;
	}
	else
		*token = (*token)->next;
	return (*token);
}

t_token	*ft_pwd(t_token **token)
{
	char	*cwd;

	if (token && ft_strncmp((*token)->content, "pwd", 3) == 0)
	{
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			ft_putstr_fd(cwd, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			free (cwd);
		}
	}
	*token = after_comand(token);
	gg()->last_status = 0;
	return (*token);
}


		// if (count)
		// {
		// 	while (count)
		// 	{
		// 		*token = (*token)->next;
		// 		count--;
		// 	}
		// }


		// if (((*token)->content) && (verify_argum(*(*token)->content)
		// 		&& (*token)->next))
		// {
		// 	gg()->last_status = 1;
		// 	*token = (*token)->next;
		// 	return (*token);
		// }