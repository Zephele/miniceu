/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pede-jes <pede-jes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:16:00 by pede-jes          #+#    #+#             */
/*   Updated: 2025/07/19 21:44:05 by pede-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int	is_alpha(char *string)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (string[i])
	{
		while(string[i] == '+' || string[i] == '-' || string[i] =='\"')
		{
		 	i++;
		}
		if(string[i])
		{
			if (!ft_isalpha(string[i]))
				flag = 1;
		}
		i++;
	}
	if (flag)
		return (0);
	return (1);

}

static	int	is_digit(char *string)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;

	while (string[i])
	{
		while(string[i] == '+' || string[i] == '-' || string[i] =='\"')
		{
		 	i++;
		}
		if(string[i])
		{
			if (!ft_isdigit(string[i]))
			flag = 1;	
		}
		i++;
	}
	if (flag)
		return (0);
	return (1);
}
static int	ft_my_atoi(const char *nptr)
{
	int	temp;
	int	negative;
	int	i;

	temp = 0;
	negative = 1;
	i = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ' || *nptr == '\"')
		nptr++;
	while (*nptr == '-' || *nptr == '+'|| *nptr == '\"')
	{
		if (*nptr == '-')
			negative = -1;
		nptr ++;
		i++;
	}
	while (*nptr != '\0' && (*nptr >= '0' && *nptr <= '9'))
	{
		temp = temp * 10 + (*nptr - '0');
		nptr++;
	}
	return (temp * negative);
}
static int	calc_exit_code(t_token **token)
{
	int exit_code;
	
	exit_code = 0;
	if(is_digit((*token)->next->content))
	{
		exit_code =  (ft_my_atoi((*token)->next->content) % 256 + 256) % 256;
	} 
	return exit_code;
}

t_token *ft_exit(t_token **token)
{
	int exit_code;
	if ((*token)->next)
	{
		if (is_digit((*token)->next->content))
		{
			if ((*token)->next->next)
			{
				if (is_alpha((*token)->next->next->content))
				{
					ft_putstr_fd("exit\n", STDERR_FILENO);
					ft_putstr_fd("minishell: too many arguments\n",
						STDERR_FILENO);
					free_tokens(*token);
					free_envs(gg()->envs);
					exit(1);
				}
				else
				{
					ft_putstr_fd("exit\n", STDERR_FILENO);
					ft_putstr_fd("minishell: too many arguments\n",
						STDERR_FILENO);
					*token = (*token)->next->next->next;
					return (*token);
				}
			}
			else
			{
				ft_putstr_fd("exit\n", STDERR_FILENO);
				exit_code = calc_exit_code(token);
				free_tokens(*token);
				free_envs(gg()->envs);

				exit(exit_code);
			}
		}
		else
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			ft_putstr_fd("minishell: numeric argument required\n",
				STDERR_FILENO);
			free_tokens(*token);
			free_envs(gg()->envs);
			exit(2);
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


