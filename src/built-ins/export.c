/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:20:14 by ratanaka          #+#    #+#             */
/*   Updated: 2025/07/17 16:59:21 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// verificacoes de entrada
//		(se tiver errado um deles apenas retorna e vai para o proximo)


static void	size_equal(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '=')
		i++;
	ft_putstr_fd("export: not an identifier: ", 2);
	write(2, str, i);
	ft_putchar('\n');
}

static int	valid_argument(char *new_env)
{
	int	i;

	i = 0;
	if (!ft_isalpha(new_env[i]))
	{
		size_equal(new_env);
		return (1);
	}
	if (ft_strchr(new_env, '='))
	{
		while (new_env[i])
		{
			while (new_env[i] != '=' && ft_isalnum_underline(new_env[i]))
				i++;
			if (new_env[i] == '=')
				return (0);
			else
			{
				size_equal(new_env);
				return (1);
			}
			i++;
		}
	}
	return (1);
}

static int	ft_new_envs(char *new_env)
{
	int		count;

	if (valid_argument(new_env))
		return (1);
	count = count_envs(gg()->envs->var);
	count = alloc_env_1(count, new_env);
	if (count == -1)
		return (1);
	if (!gg()->envs->var)
		return (1);
	return (0);
}

t_token	*ft_export(t_token **token)
{
	if (!(*token)->next)
		return (*token);
	*token = (*token)->next;
	while (*token)
	{
		if (ft_new_envs((*token)->content))
			return (*token);
		*token = (*token)->next;
	}
	return (*token);
}
