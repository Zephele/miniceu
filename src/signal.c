/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:10:14 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/21 18:49:17 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "../include/minishell.h"

static void	handle_prompt_sigint(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
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

void	handle_cmd_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	gg()->last_status = 130;
}

void	ctrl_backslash(int sig)
{
	(void)sig;
	gg()->last_status = 131;
	write(1, "Quit (core dumped)\n", 19);
}

void	setup_prompt_functions(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(sa_int));
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	sa_int.sa_handler = handle_cmd_sigint;
	sa_quit.sa_handler = ctrl_backslash;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
