/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:45:29 by ratanaka          #+#    #+#             */
/*   Updated: 2025/06/27 18:53:46 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*ft_env(t_token **token)
{
	int	i;

	i = 0;
	if (*token && (compare_aux((*token)->content, "env") == 0))
	{
		while (i < gg()->envs->count)
		{
			ft_printf("%s\n", gg()->envs->var[i]);
			i++;
		}
	}
	*token = (*token)->next;
	return (*token);
}
