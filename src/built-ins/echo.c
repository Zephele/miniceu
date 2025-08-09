/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:22:22 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/08 21:02:22 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	no_quotes_aux(char *content, char *temp, int *i, int *j)
{
	if (content[*i] == '\'')
	{
		(*i)++;
		while (content[*i] != '\'')
		{
		temp[*j] = content[*i];
			(*j)++;
			(*i)++;
		}
		(*i)++;
	}
	else if (content[*i] == '\"')
	{
			(*i)++;
		while (content[*i] != '\"')
		{
			temp[*j] = content[*i];
			(*j)++;
			(*i)++;
		}
		(*i)++;
	}
}

char	*no_quotes(char *content)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!content)
		return (NULL);
	temp = ft_strdup(content);
	while (content[i])
	{
		if (content[i] == '\'' || content[i] == '\"')
			no_quotes_aux(content, temp, &i, &j);
		else
		{
			if (content[i] == '\\' && content[i + 1])
				i++;
			else if (content[i] == '\\' && !content[i + 1])
				content[i] = ' ';
			temp[j++] = content[i++];
		}
	}
	temp[j] = '\0';
	free_safe(content);
	return (temp);
}

static int	ft_strncmp_next(const char *s1, const char *s2,
		size_t n, int *newline)
{
	size_t	i;

	i = 0;
	if ((*s1 == '\0' || *s2 == '\0') && (n == i))
		return (0);
	while ((i < n) && (*s1 != '\0' || *s2 != '\0'))
	{
		if (*s1 != *s2)
			return ((unsigned char ) *s1 - (unsigned char ) *s2);
		s1++;
		s2++;
		i++;
	}
	*newline = 0;
	return (0);
}

static void	echo_aux(t_token **token)
{
	if ((*token)->type == ARG || (*token)->type == CMD)
		(*token)->content = no_quotes((*token)->content);
	else if ((*token)->type == ENV)
		(*token)->content = expand_env_vars((*token)->content);
	ft_putstr_fd((*token)->content, STDOUT_FILENO);
	if ((*token)->next && (*token)->next->content
		&& ((*token)->next->type != PIPE
			&& (*token)->next->type != REDIR_IN
			&& (*token)->next->type != REDIR_OUT
			&& (*token)->next->type != REDIR_APPEND
			&& (*token)->next->type != HEREDOC
			&& (*token)->next->type != ENV))
		ft_putchar_fd(' ', STDOUT_FILENO);
}

t_token	*ft_echo(t_token **token)
{
	int	newline;

	newline = 1;
	if (*token && (compare_aux((*token)->content, "echo") == 0))
	{
		if ((*token)->next && (*token)->next->type != 8)
			*token = (*token)->next;
		else
			return (NULL);
		if (*token && ft_strncmp_next((*token)->content,
				"-n", 2, &newline) == 0)
			*token = (*token)->next;
		while (*token)
		{
			if ((*token)->type == ARG || (*token)->type == CMD
				|| (*token)->type == ENV)
				echo_aux(token);
			else
				return (*token);
			*token = (*token)->next;
		}
		if (newline)
			ft_putchar_fd('\n', STDOUT_FILENO);
	}
	gg()->last_status = 0;
	return (*token);
}
