/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:43:45 by ratanaka          #+#    #+#             */
/*   Updated: 2025/06/11 14:57:58 by ratanaka         ###   ########.fr       */
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

typedef struct s_env
{
	char	**vars;
}	t_env;


typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_global
{
	char	*content;
}	t_global;

# define CMD 0
# define ARG 1
# define REDIR_IN 2
# define REDIR_OUT 3
# define REDIR_APPEND 4
# define HEREDOC 5
# define PIPE 6
# define ENV 7

t_token		*tokenize(char *input, int i);
void		free_tokens(t_token *tokens);
int			seen_quotes(char *input, int i);
char		*ft_strjoin_free(char *s1, char *s2);
char		*include_quotes(char *content, char quote);
char		*extract_quoted_content(char *input, int *i, char quote);
int			validate_syntax(t_token *tokens);
t_token		*handle_env(char *input, int *i);
int			is_empty(char *temp, char *content);
t_global	*gg(void);
char		*expand_env_vars(char *content);
char		*expand_aux(char *content, int *i, int *temp_size, char *temp);
int			ft_isalnum_underline(int c);


//BUILT-INS

void		ft_echo(t_token *token);
void		ft_pwd(t_token *token);
void		ft_cd(t_token *token);

#endif