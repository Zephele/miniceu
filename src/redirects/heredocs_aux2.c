/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_aux2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:10:42 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/26 21:08:51 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*input_exec(const char *delimiter, char *input)
{
	if (delimiter[0] == '\'')
		return (input);
	else
	{
		input = expand_env_vars(input);
		return (input);
	}
}

static void	*no_input(char *deli_noquot)
{
	ft_putstr_fd("minishell: warning: here-document ", 1);
	ft_putstr_fd("delimited by end-of-file (wanted `", 1);
	ft_putstr_fd(deli_noquot, 1);
	ft_putstr_fd("')\n", 1);
	free_safe(deli_noquot);
	return (NULL);
}

void	*read_here_aux(const char *delimiter, char *input, int fd)
{
	char	*deli_noquot;

	deli_noquot = ft_strdup(delimiter);
	deli_noquot = no_quotes(deli_noquot);
	signal(SIGINT, handle_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("> ");
		if (!input)
			if (!no_input(deli_noquot))
				break ;
		input = input_exec(delimiter, input);
		if (ft_strncmp(input, deli_noquot, ft_strlen(deli_noquot)) == 0
			&& ft_strlen(input) == ft_strlen(deli_noquot))
		{
			free(input);
			free_safe(deli_noquot);
			break ;
		}
		ft_putendl_fd(input, fd);
		free(input);
	}
	close(fd);
	return ("o");
}

static void	pid_function(int pid, const char *delimiter, char *input, int fd)
{
	int	status;
	int	i;

	i = 2;
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		read_here_aux(delimiter, input, fd);
		free_pids_here();
		if (gg()->theres_pipe > 0 && gg()->segments)
			free_segments_memory(gg()->segments);
		while (i++ < 1000)
			close(i);
		exit(0);
	}
	else
	{
		close(fd);
		setup_prompt_signals();
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			gg()->last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			gg()->last_status = 128 + WTERMSIG(status);
	}
}

char	*ft_read_heredoc(const char *delimiter, int index, char *temp)
{
	char	*input;
	int		pid;
	char	*tmp_file;
	int		fd;

	input = NULL;
	tmp_file = gen_tmp_file(index);
	if (!tmp_file)
		return (NULL);
	gg()->temp_h = temp;
	gg()->temp_file_h = tmp_file;
	fd = open(tmp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror ("error opening temp file");
		free(tmp_file);
		return (NULL);
	}
	pid = fork();
	pid_function(pid, delimiter, input, fd);
	return (tmp_file);
}
