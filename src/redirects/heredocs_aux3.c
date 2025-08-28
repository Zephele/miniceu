/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_aux3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:08:09 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/28 14:31:17 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_file_reddirin(int type, const char *filename,
	t_list **tmp_files, int heres)
{
	int		fd;
	char	*tmp_file;
	char	*temp;

	fd = -1;
	tmp_file = NULL;
	temp = ft_strdup(filename);
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

t_token	*free_reddirs(t_token *current)
{
	free (current->content);
	current->content = NULL;
	current = current->next;
	if (current)
	{
		free (current->content);
		current->content = NULL;
		current = current->next;
	}
	return (current);
}
