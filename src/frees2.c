/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pede-jes <pede-jes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:52:26 by ratanaka          #+#    #+#             */
/*   Updated: 2025/07/14 21:11:29 by pede-jes         ###   ########.fr       */
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
			i++;
		}
		free(env_list->var);
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
