/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:40:57 by ratanaka          #+#    #+#             */
/*   Updated: 2025/06/27 20:14:37 by ratanaka         ###   ########.fr       */
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

static void	print_tokens(t_token *tokens)
{
	int	i;

	i = 1;
	while (tokens)
	{
		ft_printf("Token %d:\n", i++);
		ft_printf("  Content: [%s]\n", tokens->content);
		ft_printf("  Type:    %d\n", tokens->type);
		if (tokens->type == 2)
			ft_printf("  REDIR_IN\n");
		if (tokens->type == 3)
			ft_printf("  REDIR_OUT\n");
		if (tokens->type == 4)
			ft_printf("  REDIR_APPEND\n");
		if (tokens->type == 5)
			ft_printf("  HEREDOC\n");
		if (tokens->type == 6)
			ft_printf("  PIPE\n");
		ft_printf("\n");
		tokens = tokens->next;
	}
}

static void	built_ins_test(t_token *tokens)
{
	int		i;

	i = 1;
	while (tokens)
	{
		if (tokens->type == CMD || tokens->type == ARG)
		{
			if (compare_aux(tokens->content, "echo") == 0)
			{
				tokens = ft_echo(&tokens);
				if (!tokens)
					return ;
			}
			if (compare_aux(tokens->content, "cd") == 0)
			{
				tokens = ft_cd(&tokens);
				if (!tokens)
					return ;
			}
			// else if (ft_strncmp(tokens->content, "exit", 4) == 0)
			// {
			// 	ft_exit(tokens);
			// 	return ;
			// }
			if (compare_aux(tokens->content, "env") == 0)
			{
				tokens = ft_env(&tokens);
				if (!tokens)
					return ;
			}
			// else if (ft_strncmp(tokens->content, "export", 6) == 0)
			// {
			// 	ft_export(tokens);
			// 	return ;
			// }
			// else if (ft_strncmp(tokens->content, "unset", 5) == 0)
			// {
			// 	ft_unset(tokens);
			// 	return ;
			// }
			if (compare_aux(tokens->content, "pwd") == 0)
			{
				tokens = ft_pwd(&tokens);
				if (!tokens)
					return ;
			}
			if (tokens->type != CMD && tokens->type != ARG)
				tokens = tokens->next;
			else
				tokens = tokens->next;
		}
		else
			return ;
	}
}

static void	init_minishell(t_env *envs)
{
	gg()->envs = envs;
}

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_env	*envs;
	int		i;

	i = 0;
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
		tokens = tokenize(input, i);
		if (tokens && validate_syntax(tokens))
		{
			free_tokens(tokens);
			free(input);
			continue ;
		}
		if (tokens)
		{
			print_tokens(tokens);
			built_ins_test(tokens);
			free_tokens(tokens);
		}
		free(input);
	}
	free_envs(envs);
	clear_history();
	return (0);
}

// int	main(void)
// {
// 	t_token	*tokens;
// 	char	*input;

// 	signal(SIGINT, handle_sigint);
// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input)
// 		{
// 			ft_printf("exit\n");
// 			exit(0);
// 		}
// 		tokens = tokenize(input);
// 		if (!tokens)
// 		{
// 			ft_printf("Error, tokens");
// 			free(input);
// 			return (1);
// 		}
// 		ft_printf("\n=== Tokens Generated ===\n");
// 		print_tokens(tokens);
// 		free_tokens(tokens);
// 		free(input);
// 	}
// 	return (0);
// }
