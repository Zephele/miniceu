/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:19:21 by ratanaka          #+#    #+#             */
/*   Updated: 2025/07/18 16:06:03 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	remove_env_var(t_env *env, char *name)
{
	int	i;
	int	j;

	i = 0;
	while (i < env->count)
	{
		if (ft_strncmp(env->var[i], name, ft_strlen(name)) == 0
			&& env->var[i][ft_strlen(name)] == '=')
		{
			free(env->var[i]);
			j = i;
			while (j < env->count - 1)
			{
				env->var[j] = env->var[j + 1];
				j++;
			}
			env->var[j] = NULL;
			env->count--;
			return ;
		}
		i++;
	}
}

t_token	*ft_unset(t_token **token)
{
	if (!(*token)->next)
		return ((*token)->next);
	*token = (*token)->next;
	while (*token)
	{
		remove_env_var(gg()->envs, (*token)->content);
		*token = (*token)->next;
	}
	gg()->last_status = 0;
	return (*token);
}
