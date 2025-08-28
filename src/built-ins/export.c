/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pede-jes <pede-jes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:20:14 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/28 14:28:46 by pede-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	size_equal(char *str, int g1)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	ft_putstr_fd("export: `", 2);
	write(2, str, i);
	ft_putstr_fd("': not a valid identifier\n", 2);
	if (g1)
		gg()->last_status = 1;
}

static int	valid_argument_aux(int *i, char *new_env)
{
	while (new_env[*i])
	{
		while (new_env[*i] != '=' && ft_isalnum_underline(new_env[*i]))
		{
			if (!ft_isalnum_underline(new_env[*i]))
				gg()->last_status = 1;
			(*i)++;
		}
		if (new_env[*i] == '=')
			return (0);
		else
		{
			size_equal(new_env, 1);
			return (1);
		}
		(*i)++;
	}
	return (0);
}

static int	valid_argument(char *new_env)
{
	int	i;

	i = 0;
	if (!ft_isalpha(new_env[i]))
	{
		size_equal(new_env, 1);
		return (1);
	}
	if (ft_strchr(new_env, '='))
	{
		while (new_env[i])
		{
			if (valid_argument_aux(&i, new_env))
				return (1);
			else
				return (0);
		}
	}
	while (new_env[++i])
		if (!ft_isalnum_underline(new_env[i]))
			size_equal(new_env, 1);
	return (1);
}

static int	ft_new_envs(char *new_env)
{
	int		count;

	if (valid_argument(new_env))
		return (1);
	if (valid_quotes(new_env))
		new_env = cut_quotes_env(new_env);
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
	{
		list_environ_sorted(gg()->envs->var, 0, 0);
		return ((*token)->next);
	}
	*token = (*token)->next;
	while (*token)
	{
		if (ft_new_envs((*token)->content))
		{
			*token = after_comand(token);
			return (*token);
		}
		*token = (*token)->next;
	}
	gg()->last_status = 0;
	return (*token);
}
