/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:41:17 by ratanaka          #+#    #+#             */
/*   Updated: 2025/07/25 13:47:16 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>


static char	*ft_read_heredoc(const char *delimiter)
{
	char	*input;
	char	tmp_file[] = "/tmp/minishell_heredoc_XXXXXX";
	int		fd;

	fd = mkstemp(tmp_file);
	if (fd == -1)
	{
		perror ("error fd");
		return (NULL);
	}
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			perror ("input error");
			break ;
		}
		if (ft_strncmp(input, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, fd);
		ft_putstr_fd("\n", fd);
		free(input);
	}
	return (ft_strdup(tmp_file));
}

static int	open_file_reddirin(int type, const char *filename)
{
	int		fd;
	char	*tmp_file;
	char	*temp;

	tmp_file = NULL;
	fd = -1;
	temp = ft_strdup(filename);
	temp = no_quotes(temp);
	if (type == 2)
		fd = open(temp, O_RDONLY);
	else if (type == 5)
	{
		tmp_file = ft_read_heredoc(temp);
		if (!tmp_file)
		{
			free (temp);
			return (-1);
		}
		fd = open(tmp_file, O_RDONLY);
		if (fd == -1)
		{
			perror("Open file error");
			free (temp);
			free (tmp_file);
			return (-1);
		}
		unlink(tmp_file);
		free(tmp_file);
	}
	if (fd == -1)
	{
		perror("Open file error");
		free (temp);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Open file error");
		free (temp);
		close(fd);
		return (-1);
	}
	free (temp);
	close(fd);
	return (0);
}

t_token	*handle_redirects(t_token **tokens)
{
	int		saved_stdout;
	int		saved_stdin;
	t_token	*current;
	int		type;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	current = *tokens;
	while (current && current->type != PIPE)
	{
		if (current->type == 3 || current->type == 4)
		{
			type = current->type;
			while (current)
			{
				if (current->next && (current->next->content[0] == '.'
						&& current->next->content[1] == '/'))
					current = current->next;
				else if (current->next && (current->next->content[0] == '\''
						|| current->next->content[0] == '\"'))
				{
					if (current->next && (current->next->content[1] == '.'
							&& current->next->content[2] == '/'))
						current = current->next;
					else
						break ;
				}
				else
					break ;
			}
			if (open_file_reddir(type, current->content) == -1)
			{
				dup2(saved_stdout, STDOUT_FILENO);
				close(saved_stdout);
				dup2(saved_stdin, STDIN_FILENO);
				close(saved_stdin);
				gg()->last_status = 1;
				return (NULL);
			}
		}
		else if (current->type == 2 || current->type == 5)
		{
			type = current->type;
			while (current)
			{
				if (current->next && (current->next->content[0] == '.'
						&& current->next->content[1] == '/'))
					current = current->next;
				else if (current->next && (current->next->content[0] == '\''
						|| current->next->content[0] == '\"'))
				{
					if (current->next && (current->next->content[1] == '.'
							&& current->next->content[2] == '/'))
						current = current->next;
					else
						break ;
				}
				else
					break ;
			}
			if (open_file_reddirin(type, current->content) == -1)
			{
				dup2(saved_stdin, STDIN_FILENO);
				close(saved_stdin);
				dup2(saved_stdout, STDOUT_FILENO);
				close(saved_stdout);
				gg()->last_status = 1;
				return (NULL);
			}
		}
		current = current->next;
	}
	current = built_external(*tokens, gg()->envs);
	while (current && current->type != PIPE)
		current = current->next;
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	return (current);
}


//primeiro eu vou criar o arquivo temporario
//depois de ter criado, eu abro apenas para ler depois (O_RDONLY)
//quando chegar no build_external ele apenas le


		// fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		// if (fd == -1)
		// {
		// 	perror("Open file error");
		// 	return (-1);
		// }
		// if (dup2(fd, STDOUT_FILENO) == -1)
		// {
		// 	perror("Open file error");
		// 	close(fd);
		// 	return (-1);
		// }
		// if (ft_read_heredoc(filename))
		// 	return (-1);
		// close(fd);
		// fd = open(filename, O_RDONLY);