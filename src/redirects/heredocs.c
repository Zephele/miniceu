/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:41:17 by ratanaka          #+#    #+#             */
/*   Updated: 2025/07/31 16:10:34 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_read_heredoc(const char *delimiter, int index)
{
	char	*input;
	char	*tmp_file;
	int		fd;

	tmp_file = gen_tmp_file(index);
	fd = open(tmp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
		ft_putendl_fd(input, fd);
		free(input);
	}
	return (tmp_file);
}

static int	open_file_reddirin(int type, const char *filename, t_list **tmp_files, int heres)
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
		tmp_file = ft_read_heredoc(temp, gg()->here_tmp++);
		if (!tmp_file)
		{
			free (temp);
			return (-1);
		}
		ft_lstadd_back(tmp_files, ft_lstnew(ft_strdup(tmp_file)));
		fd = open(tmp_file, O_RDONLY);
		free(tmp_file);
		if (fd == -1)
		{
			perror("Open file error");
			free (temp);
			free (tmp_file);
			return (-1);
		}
	}
	if (fd == -1)
	{
		perror("Open file error");
		free (temp);
		return (-1);
	}
	if (heres == 0 || gg()->here_tmp == heres)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("Open file error");
			free (temp);
			close(fd);
			return (-1);
		}
	}
	close(fd);
	free (temp);
	return (0);
}

int	current_aux2(t_token *current)
{
	int	i;

	i = 0;
	while (current)
	{
		if (i > 0)
			break ;
		if (current->next && (current->next->content[0] == '.'
				&& current->next->content[1] == '/'))
				i++;
		else if (current->next && (current->next->content[0] == '\''
				|| current->next->content[0] == '\"'))
		{
			if (current->next && (current->next->content[1] == '.'
					&& current->next->content[2] == '/'))
				i++;
			else
				break ;
		}
		else
			break ;
	}
	return (i);
}

t_token	*handle_redirects(t_token **tokens)
{
	int		saved_stdout;
	int		saved_stdin;
	t_token	*current;
	t_list	*tmp_files;
	int		heres;
	int		type;

	tmp_files = NULL;
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	current = *tokens;
	heres = ft_hmheres(current);
	while (current && current->type != PIPE)
	{
		if (current->type == 3 || current->type == 4)
		{
			type = current->type;
			if (current)
			{
				if (current_aux2(current))
					current = current_aux(current);
				else
					current = current->next;
			}
			if (open_file_reddir(type,
					current->content) == -1)
				return (error_redir(saved_stdout, saved_stdin, &tmp_files));
		}
		else if (current->type == 2 || current->type == 5)
		{
			type = current->type;
			if (current)
			{
				if (current_aux2(current))
					current = current_aux(current);
				else
					current = current->next;
			}
			if (open_file_reddirin(type,
					current->content, &tmp_files, heres) == -1)
				return (error_redir(saved_stdout, saved_stdin, &tmp_files));
		}
		current = current->next;
	}
	if (tokens)
		current = built_external(*tokens, gg()->envs);
	while (current && current->type != PIPE)
		current = current->next;
	if (tmp_files)
		ft_lstclear(&tmp_files, free);
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