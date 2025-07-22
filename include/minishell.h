/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:43:45 by ratanaka          #+#    #+#             */
/*   Updated: 2025/07/22 20:13:12 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../libs/ft_printf/ft_printf.h"
# include "../libs/libft/libft.h"

typedef struct s_env
{
	char	**var;
	int		count;
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
	t_token	*token;
	t_env	*envs;
	int		last_status;
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
int			seen_quotes(char *input, int i);
char		*include_quotes(char *content, char quote);
char		*extract_quoted_content(char *input, int *i, char quote);
int			validate_syntax(t_token *tokens);
t_token		*handle_env(char *input, int *i);
t_global	*gg(void);
char		*expand_env_vars(char *content);
char		*expand_aux(char *content, int *i, int *temp_size, char *temp);
int			ft_isalnum_underline(int c);
char		*no_quotes(char *content);
int			compare_aux(char *content, char *comp);
char		*aux_quotes(char *input, int *i, char quote, char *content);
char		*aux_general(char *input, int *i, char *content);
int			ft_isalphupper_underline(int c);
int			ft_same_var(char *new_env, char **new, int i, int next);
int			alloc_env_1(int count, char *new_env);
t_token		*after_comand(t_token **token);

//FREES
int			is_empty(char *temp, char *content);
int			is_empty_token(char *temp, t_token *token);
void		free_tokens(t_token *tokens);
char		*ft_strjoin_free(char *s1, char *s2);
void		free_envs(t_env *env_list);
void		ft_free(char **ptr);
void		free_envs_var(char **var);

//BUILT-INS

t_token		*ft_echo(t_token **token);
t_token		*ft_pwd(t_token **token);
t_token		*ft_cd(t_token **token);
t_token		*ft_env(t_token **token);
t_token		*ft_exit(t_token **token);
void		ft_case_1(t_token **token);
void		ft_case_2(t_token **token);
int			ft_case_3(t_token **token);
void		ft_case_4(t_token **token);
void		ft_case_5(t_token **token);
int			calc_exit_code(t_token **token);
t_token		*ft_unset(t_token **token);
t_token		*ft_export(t_token **token);

//ENVS
t_env		*init_envs(char	**envp);
int			copy_envs(t_env *new, char **envp, int count);
int			count_envs(char	**envp);

//EXEC

t_token		*exec_external(t_token *tokens, t_env *envs);
t_token		*exec(t_token *tokens, t_env *envs);
t_token		*exec_biut(t_token *tokens);
int			is_biut(t_token *tokens);

//REDIRECTS

t_token		*handle_redirects(t_token **tokens);

#endif