/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_aux2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:10:42 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/01 18:46:55 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*read_here_aux(const char *delimiter, char *input, int fd)
{
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
	return ("o");
}

static char	*ft_read_heredoc(const char *delimiter, int index)
{
	char	*input;
	char	*tmp_file;
	int		fd;

	input = NULL;
	tmp_file = gen_tmp_file(index);
	fd = open(tmp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror ("error fd");
		return (NULL);
	}
	if (!read_here_aux(delimiter, input, fd))
	{
		free(tmp_file);
		return (NULL);
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
		return (-1);
	}
	return (fd);
}
