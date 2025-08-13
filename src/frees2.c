/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:52:26 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/05 20:28:00 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_envs(t_env *env_list)
{
	int	i;

	if (!env_list)
		return ;
	if (env_list->var)
	{
		i = 0;
		while (env_list->var[i])
		{
			free(env_list->var[i]);
			env_list->var[i] = NULL;
			i++;
		}
		free(env_list->var);
		env_list->var = NULL;
	}
	free(env_list);
}

void	free_envs_var(char **var)
{
	int	i;

	if (var)
	{
		i = 0;
		while (var[i])
		{
			free(var[i]);
			var[i] = NULL;
			i++;
		}
		free(var);
		var = NULL;
	}
}

void	ft_free(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		if (del)
			del(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	free_safe(void *ptr)
{
	if (ptr && ptr != NULL)
		free(ptr);
	else
		return ;
}
