/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:40:57 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/12 14:27:33 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_minishell(t_env *envs)
{
	gg()->envs = envs;
	gg()->last_status = 0;
	gg()->here_tmp = 0;
	gg()->temp_file_h = NULL;
	gg()->temp_h = NULL;
	gg()->heres = 0;
	gg()->heres_cmp = 0;
	gg()->segments = NULL;
}

static void	ml_aux(char *input)
{
	t_token	*current;
	t_token	*tokens;

	while (1)
	{
		tokens = tokenize(input, 0);
		gg()->token = tokens;
		if (tokens && validate_syntax(tokens))
		{
			free_tokens(tokens);
			return ;
		}
		if (tokens)
		{
			current = tokens;
			while (current)
				current = exec(current, gg()->envs);
			free_tokens(tokens);
		}
		return ;
	}
}

static void	main_loop(void)
{
	char	*input;

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
		ml_aux(input);
		free(input);
	}
}

int	main(void)
{
	t_env	*envs;

	envs = init_envs(__environ);
	if (!envs)
		return (1);
	init_minishell(envs);
	main_loop();
	free_envs(envs);
	clear_history();
	return (0);
}
