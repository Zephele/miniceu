/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:40:43 by ratanaka          #+#    #+#             */
/*   Updated: 2025/07/17 14:54:54 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	same_var_aux(char **new, int i, char *new_env)
{
	if (new)
	{
		free(new[i]);
		new[i] = NULL;
	}
	new[i] = ft_strdup(new_env);
}

int	ft_same_var(char *new_env, char **new, int i, int next)
{
	int	size_char_var;
	int	size_char_env;

	size_char_var = 0;
	size_char_env = 0;
	if (!gg()->envs->var[i])
		return (0);
	while (gg()->envs->var[i][size_char_var] != '=')
		size_char_var++;
	while (new_env[size_char_env] != '=')
		size_char_env++;
	if (ft_strncmp(gg()->envs->var[i], new_env, size_char_var) == 0
		&& size_char_var == size_char_env
		&& (gg()->envs->var[i][size_char_var] == '='
		&& new_env[size_char_env] == '='))
	{
		if (next)
			same_var_aux(new, i, new_env);
		return (1);
	}
	return (0);
}

static int	alloc_aux(int count, char *new_env, char **new)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (ft_same_var(new_env, new, i, 1))
			break ;
		else if (i == count - 1)
		{
			new[i] = ft_strdup(new_env);
			break ;
		}
		else
			new[i] = ft_strdup(gg()->envs->var[i]);
		if (!new[i])
		{
			perror("Error memory alocation");
			while (i > 0)
				free(new[--i]);
			free(new);
			new = NULL;
			return (-1);
		}
	}
	return (0);
}

int	alloc_env_1(int count, char *new_env)
{
	char	**new;
	int		i;

	new = NULL;
	i = -1;
	while (gg()->envs->var[++i])
	{
		if (ft_same_var(new_env, new, i, 0))
			gg()->envs->count = (count);
		else
			gg()->envs->count = (count + 1);
	}
	count = gg()->envs->count;
	new = malloc(sizeof(char *) * (count + 1));
	if (!new)
	{
		perror("Error memory alocation");
		return (-1);
	}
	ft_memset(new, '\0', (sizeof(char *) * (count + 1)));
	if (alloc_aux(count, new_env, new) == -1)
		return (-1);
	free_envs_var(gg()->envs->var);
	gg()->envs->var = new;
	return (count);
}
