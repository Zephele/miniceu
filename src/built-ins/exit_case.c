/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pede-jes <pede-jes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:37:12 by pede-jes          #+#    #+#             */
/*   Updated: 2025/07/21 21:22:17 by pede-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_case_1(t_token **token)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: too many arguments\n", STDERR_FILENO);
	free_tokens(*token);
	free_envs(gg()->envs);
	clear_history();
	exit(1);
}

void	ft_case_2(t_token **token)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: too many arguments\n", STDERR_FILENO);
	*token = (*token)->next->next->next;
}

int	ft_case_3(t_token **token)
{
	int	exit_code;

	exit_code = calc_exit_code(token);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	free_tokens(*token);
	free_envs(gg()->envs);
	clear_history();
	return (exit_code);
}

void	ft_case_4(t_token **token)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: numeric argument required\n",
		STDERR_FILENO);
	free_tokens(*token);
	free_envs(gg()->envs);
	clear_history();
	exit(2);
}

void	ft_case_5(t_token **token)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	free_tokens(*token);
	free_envs(gg()->envs);
	clear_history();
}
