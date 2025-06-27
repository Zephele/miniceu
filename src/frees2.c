/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:52:26 by ratanaka          #+#    #+#             */
/*   Updated: 2025/06/27 17:58:44 by ratanaka         ###   ########.fr       */
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
