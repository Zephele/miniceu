/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_aux2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:10:42 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/06 18:30:08 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_pids_here(void)
{
	free_tokens(gg()->token);
	free_envs(gg()->envs);
	free(gg()->temp_h);
	free(gg()->temp_file_h);
	clear_history();
}

static void	handle_heredoc_sigint(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	free_pids_here();
	exit(130);
}

void	*read_here_aux(const char *delimiter, char *input, int fd)
{
	signal(SIGINT, handle_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			perror ("input error");
			break ;
		}
		input = expand_env_vars(input);
		if (ft_strncmp(input, delimiter, ft_strlen(input)) == 0)
		{
			free(input);
			break ;
		}
		ft_putendl_fd(input, fd);
		free(input);
	}
	close(fd);
	return ("o");
}

static char	*ft_read_heredoc(const char *delimiter, int index, char *temp)
{
	char	*input;
	int		pid;
	int		status;
	char	*tmp_file;
	int		fd;

	input = NULL;
	tmp_file = gen_tmp_file(index);
	gg()->temp_h = temp;
	gg()->temp_file_h = tmp_file;
	fd = open(tmp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror ("error fd");
		return (NULL);
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		read_here_aux(delimiter, input, fd);
		free_pids_here();
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			gg()->last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			gg()->last_status = 128 + WTERMSIG(status);
	}
	return (tmp_file);
}

int	open_file_reddirin(int type, const char *filename,
	t_list **tmp_files, int heres)
{
	int		fd;
	char	*tmp_file;
	char	*temp;

	fd = -1;
	tmp_file = NULL;
	temp = ft_strdup(filename);
	temp = no_quotes(temp);
	if (type == 2)
		fd = open(temp, O_RDONLY);
	else if (type == 5)
		fd = here_open_aux(fd, tmp_file, temp, tmp_files);
	if (fd == -1)
		return (exit_file(fd, temp, 1));
	if (heres == 0 || gg()->here_tmp == heres)
		if (dup2(fd, STDIN_FILENO) == -1)
			return (exit_file(fd, temp, 2));
	close(fd);
	free (temp);
	return (0);
}

int	here_open_aux(int fd, char *tmp_file,
				char *temp, t_list **tmp_files)
{
	t_list	*new_node;

	tmp_file = ft_read_heredoc(temp, gg()->here_tmp++, temp);
	if (!tmp_file)
	{
		free (temp);
		return (-1);
	}
	new_node = ft_lstnew(ft_strdup(tmp_file));
	ft_lstadd_back(tmp_files, new_node);
	fd = open(tmp_file, O_RDONLY);
	free(tmp_file);
	free(new_node);
	if (fd == -1)
	{
		perror("Open file error");
		free (temp);
		return (-1);
	}
	return (fd);
}
