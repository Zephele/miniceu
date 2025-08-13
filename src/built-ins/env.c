/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:45:29 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/12 18:38:00 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_getenv(char *env)
{
	int	i;

	i = 0;
	if (env)
	{
		while (gg()->envs->var[i])
		{
			if (!ft_strncmp(gg()->envs->var[i], env, ft_strlen(env)))
				return (&gg()->envs->var[i][ft_strlen(env) + 1]);
			i++;
		}
	}
	return (NULL);
}

t_token	*ft_env(t_token **token)
{
	int	i;

	i = 0;
	if (*token && (compare_aux((*token)->content, "env") == 0))
	{
		while (i < gg()->envs->count)
		{
			ft_printf("%s\n", gg()->envs->var[i]);
			i++;
		}
	}
	*token = (*token)->next;
	gg()->last_status = 0;
	return (*token);
}
