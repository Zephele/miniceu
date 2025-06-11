/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:22:22 by ratanaka          #+#    #+#             */
/*   Updated: 2025/06/11 13:23:14 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*no_quotes(char *content)
{
	char	*temp;
	size_t	i;

	i = ft_strlen(content);
	temp = ft_substr(content, 1, i - 2);
	free(content);
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

void	ft_echo(t_token *token)
{
	int	newline;

	newline = 1;
	if (token && ft_strncmp(token->content, "echo", 4) == 0)
	{
		token = token->next;
		if (token && ft_strncmp_next(token->content, "-n", 2, &newline) == 0)
			token = token->next;
		while (token)
		{
			if (token->type == ARG || token->type == CMD || token->type == ENV)
			{
				if (token->type == ARG)
					token->content = no_quotes(token->content);
				else if (token->type == ENV)
					token->content = expand_env_vars(token->content);
				ft_putstr_fd(token->content, STDOUT_FILENO);
				if (token->next)
					ft_putchar_fd(' ', STDOUT_FILENO);
			}
			token = token->next;
		}
		if (newline)
			ft_putchar_fd('\n', STDOUT_FILENO);
	}
}
