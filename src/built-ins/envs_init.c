/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:37:14 by ratanaka          #+#    #+#             */
/*   Updated: 2025/06/26 19:37:27 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_envs(char	**envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

t_env	*init_envs(char	**envp)
{
	int	count;

	count = count_envs(envp);
}