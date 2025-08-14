/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:07:28 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/14 14:28:26 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isalnum_underline(int c)
{
	if ((c >= 48 && c <= 57) || ((c >= 65 && c <= 90)
			|| (c >= 97 && c <= 122)) || (c == '_'))
	{
		return (1);
	}
	return (0);
}

int	compare_aux(char *content, char *comp)
{
	int	len;
	int	content_len;

	if (!content || !comp)
		return (1);
	len = ft_strlen(comp);
	content_len = ft_strlen(content);
	if (ft_strncmp(content, comp, len) == 0)
		return (0);
	else if (content_len == (len + 2)
		&& content[0] == '\'' && content[len + 1] == '\''
		&& ft_strncmp(content + 1, comp, len) == 0)
		return (0);
	else if (content_len == (len + 2)
		&& content[0] == '\"' && content[len + 1] == '\"'
		&& ft_strncmp(content + 1, comp, len) == 0)
		return (0);
	else
		return (1);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	free (content);
	return (new_node);
}

void	newline_aux(int newline)
{
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
