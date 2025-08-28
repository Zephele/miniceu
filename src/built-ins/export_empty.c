/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:27:53 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/28 10:49:44 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_env_vars(char **env, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

static void	print_sorted_env(char **env)
{
	int		i;
	char	*var;

	i = 0;
	while (env[i])
	{
		var = env[i];
		write(1, "declare -x ", 11);
		while (*var && *var != '=')
			write(1, var++, 1);
		if (*var == '=')
		{
			write(1, var++, 1);
			write(1, "\"", 1);
			while (*var)
				write(1, var++, 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}

static void	sort_env_vars(char **env, int count, int i, int j)
{
	char	*temp;
	int		len1;
	int		len2;
	int		compare_len;

	while (i++ < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			len1 = ft_strcspn(env[j], "=");
			len2 = ft_strcspn(env[j + 1], "=");
			if (len1 < len2)
				compare_len = len1;
			else
				compare_len = len2;
			if (ft_strncmp(env[j], env[j + 1], compare_len) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
	}
}

void	list_environ_sorted(char **environ, int count, int i)
{
	char	**sorted_env;

	while (environ[count])
		count++;
	sorted_env = malloc(sizeof(char *) * (count + 1));
	if (!sorted_env)
		return ;
	while (i < count)
	{
		sorted_env[i] = ft_strdup(environ[i]);
		if (!sorted_env[i])
		{
			while (--i >= 0)
				free(sorted_env[i]);
			free(sorted_env);
			return ;
		}
		i++;
	}
	sorted_env[count] = NULL;
	sort_env_vars(sorted_env, count, 0, 0);
	print_sorted_env(sorted_env);
	free_env_vars(sorted_env, count);
}
