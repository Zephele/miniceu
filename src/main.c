/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:40:57 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/06 12:38:52 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

	envs = init_envs(__environ);
	if (!envs)
		return (1);
	init_minishell(envs);
	while (1)
	{
		setup_prompt_signals();
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		add_history(input);
		tokens = tokenize(input, 0);
		gg()->token = tokens;
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

