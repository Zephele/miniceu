/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:27:53 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/13 15:00:30 by ratanaka         ###   ########.fr       */
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

static void	print_export_var(char *var)
{
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
}

static void	print_sorted_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		print_export_var(env[i]);
		i++;
	}
}

static void	sort_env_vars(char **env, int count)
{
	int		i;
	int		j;
	char	*temp;
	int		len1;
	int		len2;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			len1 = strcspn(env[j], "=");
			len2 = strcspn(env[j + 1], "=");
			if (ft_strncmp(env[j], env[j + 1], len1 < len2 ? len1 : len2) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	list_environ_sorted(char **environ)
{
	char		**sorted_env;
	int			count;
	int			i;

	count = 0;
	while (environ[count])
		count++;
	sorted_env = malloc(sizeof(char *) * (count + 1));
	if (!sorted_env)
		return ;
	i = 0;
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
	sort_env_vars(sorted_env, count);
	print_sorted_env(sorted_env);
	free_env_vars(sorted_env, count);
}

int	export_builtin(void)
{
	list_environ_sorted(gg()->envs->var);
	return (0);
}
