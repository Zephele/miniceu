/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:40:57 by ratanaka          #+#    #+#             */
/*   Updated: 2025/05/19 11:59:10 by ratanaka         ###   ########.fr       */
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

int	main(void)
{
	char	*input;
	t_token	*tokens;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		add_history(input);
		tokens = tokenize(input);
		if (tokens)
		{
			print_tokens(tokens);
			free_tokens(tokens);
		}
		free(input);
	}
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
