/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:53:49 by ratanaka          #+#    #+#             */
/*   Updated: 2025/07/16 17:45:23 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_realloc_aux(char **old_ptr, int old_size,
	int new_size, char **new_ptr)
{
	int	i;

	i = 0;
	while (i < old_size && i < new_size && old_ptr[i])
	{
		new_ptr[i] = ft_strdup(old_ptr[i]);
		if (!new_ptr[i])
		{
			while (i > 0)
				free(new_ptr[--i]);
			free(new_ptr);
			return (1);
		}
	i++;
	}
	return (0);
}

char	**ft_realloc(char **old_ptr, int old_size, int new_size)
{
	char	**new_ptr;
	int		i;

	new_ptr = malloc(sizeof(char *) * new_size);
	if (!new_ptr)
	{
		perror("Error memory allocation");
		return (NULL);
	}
	i = 0;
	while (i < new_size)
		new_ptr[i++] = NULL;
	if (old_ptr)
		if (ft_realloc_aux(old_ptr, old_size, new_size, new_ptr))
			return (NULL);
	if (old_ptr)
	{
		i = 0;
		while (i < old_size && old_ptr[i])
			free(old_ptr[i++]);
		free(old_ptr);
	}
	return (new_ptr);
}

static int	is_valid_export_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[0] || ft_isdigit(arg[0]))
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum_underline(arg[i]))
			return (0);
		i++;
	}
	if (arg[i] != '=')
		return (0);
	return (1);
}

static void	add_env_var(t_env *env, char *new_env)
{
	char	**new_var;
	int		count;
	int		i;

	if (!is_valid_export_arg(new_env))
	{
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(new_env, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return ;
	}
	count = env->count;
	i = 0;
	while (i < count)
	{
		if (ft_strncmp(env->var[i], new_env,
				ft_strchr(new_env, '=') - new_env) == 0
			&& env->var[i][ft_strchr(new_env, '=') - new_env] == '=')
		{
			free(env->var[i]);
			env->var[i] = ft_strdup(new_env);
			return ;
		}
		i++;
	}
	new_var = ft_realloc(env->var, count, count + 2);
	if (!new_var)
	{
		perror("Error memory allocation");
		return ;
	}
	env->var = new_var;
	env->var[count] = ft_strdup(new_env);
	env->var[count + 1] = NULL;
	env->count = count + 1;
}

t_token	*ft_export(t_token **token)
{
	int	i;

	if (!(*token)->next)
	{
		i = 0;
		while (i < gg()->envs->count)
		{
			ft_printf("declare -x %s\n", gg()->envs->var[i]);
			i++;
		}
		*token = (*token)->next;
		return (*token);
	}
	*token = (*token)->next;
	while (*token)
	{
		add_env_var(gg()->envs, (*token)->content);
		*token = (*token)->next;
	}
	return (*token);
}
