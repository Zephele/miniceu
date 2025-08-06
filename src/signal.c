/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:10:14 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/06 13:40:04 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "../include/minishell.h"

static void	handle_prompt_sigint(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	gg()->last_status = 130;
}

void	setup_prompt_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(sa_int));
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	sa_int.sa_handler = handle_prompt_sigint;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

// Manipulador para SIGINT durante comandos
static void	handle_cmd_sigint(int signal)
{
	(void)signal;
	gg()->last_status = 130;
	write(1, "\n", 1);
}

// Configuração de sinais para comandos
void	setup_cmd_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(sa_int));
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	sa_int.sa_handler = handle_cmd_sigint;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
