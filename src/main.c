/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:40:57 by ratanaka          #+#    #+#             */
/*   Updated: 2025/06/10 17:37:11 by ratanaka         ###   ########.fr       */
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

// static void	print_tokens(t_token *tokens)
// {
// 	int	i;

// 	i = 1;
// 	while (tokens)
// 	{
// 		ft_printf("Token %d:\n", i++);
// 		ft_printf("  Content: [%s]\n", tokens->content);
// 		ft_printf("  Type:    %d\n", tokens->type);
// 		if (tokens->type == 2)
// 			ft_printf("  REDIR_IN\n");
// 		if (tokens->type == 3)
// 			ft_printf("  REDIR_OUT\n");
// 		if (tokens->type == 4)
// 			ft_printf("  REDIR_APPEND\n");
// 		if (tokens->type == 5)
// 			ft_printf("  HEREDOC\n");
// 		if (tokens->type == 6)
// 			ft_printf("  PIPE\n");
// 		ft_printf("\n");
// 		tokens = tokens->next;
// 	}
// }

static void	built_ins_test(t_token *tokens)
{
	int	i;

	i = 1;
	while (tokens)
	{
		if (tokens->type == CMD)
		{
			if (ft_strncmp(tokens->content, "echo", 4) == 0)
			{
				echo(tokens);
				return ;
			}
			else if (ft_strncmp(tokens->content, "pwd", 3) == 0)
			{
				pwd(tokens);
				return ;
			}
			else
				tokens = tokens->next;
		}
		else
			return ;
	}
}

int	main(void)
{
	char	*input;
	t_token	*tokens;
	int		i;

	i = 0;
	signal(SIGINT, handle_sigint);
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
			built_ins_test(tokens);
			free_tokens(tokens);
		}
		free(input);
	}
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
