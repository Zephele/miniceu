/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:37:14 by ratanaka          #+#    #+#             */
/*   Updated: 2025/06/27 18:07:55 by ratanaka         ###   ########.fr       */
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

static t_env	*alloc_env(int count)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		perror("Error memory alocation");
		return (NULL);
	}
	new->var = malloc(sizeof(char *) * (count + 1));
	if (!new->var)
	{
		perror("Error memory alocation");
		free(new);
		return (NULL);
	}
	return (new);
}

static int	copy_envs(t_env *new, char **envp, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new->var[i] = ft_strdup(envp[i]);
		if (!new->var[i])
		{
			perror("Error memory alocation");
			while (i > 0)
				free(new->var[--i]);
			free(new->var);
			new->var = NULL;
			return (1);
		}
		i++;
	}
	new->var[count] = NULL;
	new->count = count;
	return (0);
}

t_env	*init_envs(char	**envp)
{
	t_env	*new;
	int		count;

	if (!envp)
		return (NULL);
	count = count_envs(envp);
	new = alloc_env(count);
	if (!new)
		return (NULL);
	if (copy_envs(new, envp, count))
	{
		free_envs(new);
		return (NULL);
	}
	return (new);
}
