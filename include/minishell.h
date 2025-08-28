/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:43:45 by ratanaka          #+#    #+#             */
/*   Updated: 2025/08/28 14:01:22 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <sys/signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <termios.h>
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

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_global
{
	char			*content;
	t_token			*token;
	t_env			*envs;
	int				last_status;
	t_list			*list;
	int				here_tmp;
	int				heres;
	int				heres_cmp;
	int				theres_pipe;
	char			*temp_h;
	char			*temp_file_h;

	t_token			**segments;
	t_token			*seg1;
	t_token			*seg2;
	int				**pipes;
	char			*heredoc_file;
	pid_t			*pids;
	int				pipe_count;
	t_token			*new_token;
	t_token			*temp;
	t_token			*new;
	char			*input_f;
	struct termios	original_term;
}	t_global;

# define CMD 0
# define ARG 1
# define REDIR_IN 2
# define REDIR_OUT 3
# define REDIR_APPEND 4
# define HEREDOC 5
# define PIPE 6
# define ENV 7
# define NOT 8

t_token		*tokenize(char *input, int i);
int			seen_quotes(char *input, int i);
char		*extract_quoted_content(char *input, int *i, char quote);
int			validate_syntax(t_token *tokens);
t_global	*gg(void);
char		*expand_env_vars(char *content);
char		*expand_aux(char *content, int *i, int *temp_size, char *temp);
int			ft_isalnum_underline(int c);
char		*no_quotes(char *content);
int			compare_aux(char *content, char *comp);
char		*aux_quotes(char *input, int *i, char quote, char *content);
char		*aux_general(char *input, int *i, char *content);
int			ft_same_var(char *new_env, char **new, int i, int next);
int			alloc_env_1(int count, char *new_env);
t_token		*after_comand(t_token **token);
t_list		*ft_lstnew(void *content);
t_token		*copy_tokens(t_token *tokens);
void		*newline_aux(int newline);
size_t		ft_strcspn(const char *s, const char *reject);

//FREES

int			is_empty(char *temp, char *content);
int			is_empty_token(char *temp, t_token *token);
void		free_tokens(t_token *tokens);
char		*ft_strjoin_free(char *s1, char *s2);
void		free_envs(t_env *env_list);
void		ft_free(char **ptr);
void		free_envs_var(char **var);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		free_safe(void *ptr);
void		free_pids_here(void);
void		free_pipe(void);
void		free_pipe_2(void);

//BUILT-INS

t_token		*ft_echo(t_token **token);
t_token		*ft_pwd(t_token **token);
t_token		*ft_cd(t_token **token);
t_token		*ft_env(t_token **token);
t_token		*ft_exit(t_token **token);
void		ft_case_1(t_token **token);
void		*ft_case_2(t_token **token);
int			ft_case_3(t_token **token);
void		ft_case_4(t_token **token);
void		ft_case_5(t_token **token);
int			calc_exit_code(t_token **token);
t_token		*ft_unset(t_token **token);
t_token		*ft_export(t_token **token);
void		list_environ_sorted(char **environ, int count, int i);

//ENVS

t_env		*init_envs(char	**envp);
int			copy_envs(t_env *new, char **envp, int count);
int			count_envs(char	**envp);

//EXEC

t_token		*exec_external(t_token *tokens, t_env *envs);
t_token		*exec(t_token *tokens, t_env *envs);
t_token		*exec_biut(t_token *tokens);
int			is_biut(t_token *tokens);
int			there_is_redir(t_token *tokens);
char		*get_path_env(char **envp);
char		*find_executable(const char *cmd, char **envp);
void		*get_exec_aux(t_token *tokens);
void		exec_errors(char *exec_path);

//PIPES
t_token		*handle_pipes(t_token *tokens, t_env *envs);
t_token		*exec_single_pipe(t_token *left_tokens,
				t_token *right_tokens, t_env *envs);
t_token		*exec_multiple_pipes(t_token *tokens);
int			count_pipes(t_token *tokens);
t_token		**split_by_pipes(t_token *tokens);
void		execute_pipe_segment(t_token *tokens, int input_fd,
				int output_fd, t_env *envs);
void		free_pipes_memory(int **pipes, int pipe_count);
void		free_segments_memory(t_token **segments);
int			count_pipes(t_token *tokens);
t_token		*copy_until_pipe(t_token *start, t_token *end);
void		wait_all_processes(pid_t *pids, int pipe_count);
void		setup_child_process(int **pipes, int pipe_count, int i);
void		create_child_processes(t_token **segments,
				int **pipes, pid_t *pids);
void		create_pipes(int **pipes, int pipe_count);
void		close_all_pipes(int **pipes, int pipe_count);
char		*ft_getenv(char *env);
t_token		*find_heredoc_token(t_token *tokens);

void		heredoc_loop(t_token *tokens);

//REDIRECTS

t_token		*handle_redirects(t_token **tokens);
int			open_file_reddir(int type, const char *filename);
t_token		*built_external(t_token *tokens, t_env *envs);
void		built_external_aux(t_token *current);
t_token		*b_a2(t_token *current);
int			exit_file(int fd, char *temp, int i);
int			copy_aux(t_token *new, t_token *current,
				t_token *head, t_token *prev);
t_token		*built_aux(t_token *current);
void		free_exec(char *exec_path);
t_token		*built_external_aux1(t_token *current);

//HEREDOCS

char		*gen_tmp_file(int index);
void		ft_lstadd_back(t_list **lst, t_list *new);
int			ft_hmheres(t_token *current);
void		*error_redir(int saved_stdout,
				int saved_stdin, t_list **lst, int i);
t_token		*current_aux(t_token *current);
int			here_open_aux(int fd, char *tmp_file,
				char *temp, t_list **tmp_files);
char		*ft_read_heredoc(const char *delimiter, int index, char *temp);

//SIGNAL

void		setup_prompt_signals(void);
void		handle_heredoc_sigint(int signal);
void		setup_prompt_functions(void);

#endif