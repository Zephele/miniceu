/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:40:57 by ratanaka          #+#    #+#             */
/*   Updated: 2025/07/31 13:10:05 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_signal;

void	handle_sigint(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	init_minishell(t_env *envs)
{
	gg()->envs = envs;
	gg()->last_status = 0;
	gg()->here_tmp = 0;
}

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_env	*envs;
	t_token	*current;

	signal(SIGINT, handle_sigint);
	envs = init_envs(__environ);
	if (!envs)
		return (1);
	init_minishell(envs);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		add_history(input);
		tokens = tokenize(input, 0);
		if (tokens && validate_syntax(tokens))
		{
			free_tokens(tokens);
			free(input);
			continue ;
		}
		if (tokens)
		{
			current = tokens;
			while (current)
				current = exec(current, gg()->envs);
			free_tokens(tokens);
		}
		free(input);
	}
	free_envs(envs);
	clear_history();
	return (0);
}

