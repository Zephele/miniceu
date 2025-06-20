/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:07:28 by ratanaka          #+#    #+#             */
/*   Updated: 2025/06/20 20:37:17 by ratanaka         ###   ########.fr       */
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

	len = ft_strlen(comp);
	if (ft_strncmp(content, comp, len) == 0)
		return (0);
	else if (content[0] == '\'' && content[len + 1] == '\''
		&& ft_strncmp(content + 1, comp, len) == 0)
		return (0);
	else if (content[0] == '\"' && content[len + 1] == '\"'
		&& ft_strncmp(content + 1, comp, len) == 0)
		return (0);
	else
		return (1);
}
