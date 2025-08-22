/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:41:17 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/21 19:02:47 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	open_file_reddirin(int type, const char *filename,
	t_list **tmp_files)
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
	gg()->heres_cmp += 1;
	if (gg()->heres == 0 || gg()->heres == 1 || gg()->heres_cmp == gg()->heres)
		if (dup2(fd, STDIN_FILENO) == -1)
			return (exit_file(fd, temp, 2));
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

static void	*handle_aux(t_token *current, t_list	*tmp_files,
	int saved_stdout, int saved_stdin)
{
	int	type;

	if (current->type == 3 || current->type == 4
		|| current->type == 2 || current->type == 5)
	{
		type = current->type;
		if (current)
		{
			if (current_aux2(current))
				current = current_aux(current);
			else
				current = current->next;
		}
		if (type == 3 || type == 4)
			if (open_file_reddir(type,
					current->content) == -1)
				return (error_redir(saved_stdout, saved_stdin, &tmp_files, 1));
		if (type == 2 || type == 5)
			if (open_file_reddirin(type,
					current->content, &tmp_files) == -1)
				return (error_redir(saved_stdout, saved_stdin, &tmp_files, 1));
	}
	return ("o");
}

static void	*loop_heres(t_token *current, t_list *tmp_files,
	int saved_stdout, int saved_stdin)
{
	while (current && current->type != PIPE)
	{
		if (handle_aux(current, tmp_files, saved_stdout,
				saved_stdin) == NULL)
			return (NULL);
		current = current->next;
	}
	return ("o");
}

t_token	*handle_redirects(t_token **tokens)
{
	int		saved_stdout;
	int		saved_stdin;
	t_token	*current;
	t_list	*tmp_files;

	tmp_files = NULL;
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	current = *tokens;
	gg()->heres = ft_hmheres(current);
	gg()->heres_cmp = 0;
	if (!gg()->heredoc_file)
		if (!loop_heres(current, tmp_files, saved_stdout, saved_stdin))
			return (NULL);
	if (tokens)
		current = built_external(*tokens, gg()->envs);
	while (current && current->type != PIPE)
		current = current->next;
	if (tmp_files)
		ft_lstclear(&tmp_files, free);
	error_redir(saved_stdout, saved_stdin, NULL, 2);
	return (current);
}
