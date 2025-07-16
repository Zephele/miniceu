/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:20:14 by ratanaka          #+#    #+#             */
/*   Updated: 2025/07/16 17:08:56 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
1. Verificar se a '='
2. Verificar se ate chegar no '=' 'e letra maiuscula ou '_'
3. realloc pra colocar a env na struct
*/

static t_env	*alloc_env_1(int count)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		perror("Error memory alocation");
		return (NULL);
	}
	new->var = malloc(sizeof(char *) * (count + 2));
	if (!new->var)
	{
		perror("Error memory alocation");
		free(new);
		return (NULL);
	}
	return (new);
}

int	copy_envs_1(t_env *new, char **var, int count, char *new_env)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (i == count - 1)
		{
			new->var[i] = ft_strdup(new_env);
			break ;
		}
		new->var[i] = ft_strdup(var[i]);
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

static t_env	*ft_new_envs(char *new_env)
{
	t_env	*new;
	int		count;
	int		temp;

	count = count_envs(gg()->envs->var);
	new = alloc_env_1(count);
	if (!new)
		return (NULL);
	temp = copy_envs_1(new, gg()->envs->var, count, new_env);
	if (temp)
	{
		free_envs(new);
		return (NULL);
	}
	// if (!temp)
	// 	free_envs(gg()->envs);
	return (new);
}

static t_env	*add_env_var(char *new_env)
{
	t_env	*new;
	int		i;

	i = 0;
	while (ft_isalnum_underline(new_env[i]))
		i++;
	if (new_env[i] == '=')
		i++;
	new = ft_new_envs(new_env);
	if (!new)
		return (NULL);
	return (new);
}

t_token	*ft_export(t_token **token)
{
	if (!(*token)->next)
		return (*token);
	*token = (*token)->next;
	if (*token)
	{
		(gg()->envs) = add_env_var((*token)->content);
		*token = (*token)->next;
	}
	return (*token);
}
