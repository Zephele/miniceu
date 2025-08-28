/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pede-jes <pede-jes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:45:29 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/28 14:49:25 by pede-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_getenv(char *env)
{
	int	i;
	int	env_len;

	i = 0;
	if (!env)
		return (NULL);
	env_len = ft_strlen(env);
	while (gg()->envs->var[i])
	{
		if (!ft_strncmp(gg()->envs->var[i], env, env_len)
			&& gg()->envs->var[i][env_len] == '=')
			return (&gg()->envs->var[i][env_len + 1]);
		i++;
	}
	return (NULL);
}

t_token	*ft_env(t_token **token)
{
	int	i;

	i = 0;
	if (*token && (compare_aux((*token)->content, "env") == 0))
	{
		if ((*token)->next)
		{
			*token = (*token)->next;
			gg()->last_status = 0;
			return (*token);
		}
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
