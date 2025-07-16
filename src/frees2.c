/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:52:26 by ratanaka          #+#    #+#             */
/*   Updated: 2025/07/16 16:18:17 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_envs(t_env *env_list)
{
	int	i;

	if (!env_list)
		return ;
	if (env_list->var)
	{
		i = 0;
		while (env_list->var[i])
		{
			free(env_list->var[i]);
			env_list->var[i] = NULL;
			i++;
		}
		free(env_list->var);
		env_list->var = NULL;
	}
	free(env_list);
}

void	ft_free(char **ptr)
{
    int	i;

    if (!ptr)
        return ;
    i = 0;
    while (ptr[i])
    {
        free(ptr[i]);
        i++;
    }
    free(ptr);
}

void	free_envs_2(void)
{
	if (gg()->envs)
		free_envs(gg()->envs);
	if (gg()->start_envs)
		free_envs(gg()->start_envs);
}
