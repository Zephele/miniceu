/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:16:00 by pede-jes          #+#    #+#             */
/*   Updated: 2025/06/30 20:01:05 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int	is_alpha(char *string)
{
		int i;
		int flag;

		i = 0;
		flag = 0;
		
		while (string[i])
		{
			if(!ft_isalpha(string[i]))	
			{
				flag = 1;
			}
			i++;
		}
		if(flag)
			return 0;
		return(1);
		
}

static	int	is_digit(char *string)
{
		int i;
		int flag;

		i = 0;
		flag = 0;
		
		while (string[i])
		{
			if(!ft_isdigit(string[i]))	
			{
				flag = 1;
			}
			i++;
		}
		if(flag)
			return 0;
		return(1);
		
}
t_token *ft_exit(t_token **token)
{
	
	if((*token)->next)
	{
		if(is_digit((*token)->next->content) )
		{
			if((*token)->next->next)
			{
				if(is_alpha((*token)->next->next->content))
				{
					ft_putstr_fd("exit\n", STDERR_FILENO);
					ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
					free_tokens(*token);
					free_envs(gg()->envs);
					exit(0);
				}else
				{
					ft_putstr_fd("exit\n", STDERR_FILENO);
					ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
					*token = (*token)->next->next->next;
					return (*token);
				}
			}
			else
			{
				ft_putstr_fd("exit\n", STDERR_FILENO);
				free_tokens(*token);
				free_envs(gg()->envs);
				exit(0);
			}
		}else
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			ft_putstr_fd("minishell: exit:numeric argument required\n", STDERR_FILENO);
			free_tokens(*token);
			free_envs(gg()->envs);
			exit(0);
		}
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	free_tokens(*token);
	free_envs(gg()->envs);
	clear_history();
	exit(0);
//pipe
//redirect > ver se realmente da exit

// calculo de valor negativo numeric argument required
// caso de 18 argumentos maximos !
// saida de env e codigo de saida confomre parametro nuḿerico !
}