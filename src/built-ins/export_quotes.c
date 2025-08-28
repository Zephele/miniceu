/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pede-jes <pede-jes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:11:01 by pede-jes          #+#    #+#             */
/*   Updated: 2025/08/28 14:29:24 by pede-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	valid_quotes(char *new_env)
{
	int	i;

	i = 0;
	while (new_env[i])
	{
		if (new_env[i] == '\'' || new_env[i] == '\"')
			return (1);
		(i)++;
	}
	return (0);
}

char	*cut_quotes_env(char *new_env)
{
	int	i;

	i = 0;
	while (new_env[i] != '\"' && new_env[i] != '\'')
		i++;
	while ((new_env[i + 1] != '\'' && new_env[i + 1] != '\"') && new_env[i + 1])
	{
		new_env[i] = new_env[i + 1];
		i++;
	}
	while (new_env[i] != '\0')
	{
		new_env[i] = '\0';
		i++;
	}
	return (new_env);
}
