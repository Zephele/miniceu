/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:43:45 by ratanaka          #+#    #+#             */
/*   Updated: 2025/05/15 18:53:21 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include "../libs/ft_printf/ft_printf.h"
# include "../libs/libft/libft.h"

typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
}	t_token;

# define CMD 0
# define ARG 1
# define REDIR_IN 2
# define REDIR_OUT 3
# define REDIR_APPEND 4
# define HEREDOC 5
# define PIPE 6

t_token	*tokenize(char *input);
void	free_tokens(t_token *tokens);

#endif