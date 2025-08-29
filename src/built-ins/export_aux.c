/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:40:43 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/29 12:41:52 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	find_var_index(char *new_env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strcspn(new_env, "=");
	while (gg()->envs->var[i])
	{
		if (ft_strncmp(gg()->envs->var[i], new_env, len) == 0
			&& gg()->envs->var[i][len] == '=')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

static int	replace_existing_var(char *new_env)
{
	int	index;

	index = find_var_index(new_env);
	if (index != -1)
	{
		free(gg()->envs->var[index]);
		gg()->envs->var[index] = ft_strdup(new_env);
		if (!gg()->envs->var[index])
		{
			perror("Error memory alocation");
			return (-1);
		}
		return (1);
	}
	return (0);
}

static char	**copy_envs_to_new_array(int count)
{
	char	**new_vars;
	int		i;

	new_vars = malloc(sizeof(char *) * (count + 2));
	if (!new_vars)
	{
		perror("Error memory alocation");
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		new_vars[i] = ft_strdup(gg()->envs->var[i]);
		if (!new_vars[i])
		{
			while (--i >= 0)
				free(new_vars[i]);
			free(new_vars);
			return (NULL);
		}
		i++;
	}
	return (new_vars);
}

static int	add_new_var(int count, char *new_env)
{
	char	**new_vars;
	int		i;

	new_vars = copy_envs_to_new_array(count);
	if (!new_vars)
		return (-1);
	i = count;
	new_vars[i] = ft_strdup(new_env);
	if (!new_vars[i])
	{
		while (--i >= 0)
			free(new_vars[i]);
		free(new_vars);
		return (-1);
	}
	new_vars[i + 1] = NULL;
	free_envs_var(gg()->envs->var);
	gg()->envs->var = new_vars;
	gg()->envs->count++;
	return (0);
}

int	alloc_env_1(int count, char *new_env)
{
	if (replace_existing_var(new_env) == 1)
		return (count);
	return (add_new_var(count, new_env));
}
