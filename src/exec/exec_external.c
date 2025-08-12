/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:21:27 by pede-jes          #+#    #+#             */
/*   Updated: 2025/08/12 19:33:23 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**build_argv(t_token *tokens)
{
	static char	*argv[256];
	t_token		*tmp;
	int			i;

	if (tokens->type == ENV && (tokens->content[1] != '?'
			&& tokens->content[2] != '\0'))
		tokens->content = expand_env_vars(tokens->content);
	tmp = tokens;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		tmp->content = no_quotes(tmp->content);
		argv[i++] = tmp->content;
		tmp = tmp->next;
	}
	argv[i] = NULL;
	return (argv);
}

static char	*get_exec_path(char **argv, t_env *envs, t_token *tokens)
{
	char	*exec_path;

	if (ft_strchr(argv[0], '/'))
		exec_path = ft_strdup(argv[0]);
	else
		exec_path = find_executable(argv[0], envs->var);
	if (!exec_path)
	{
		if (tokens->type == ENV && (tokens->content[0] == '$'
				&& tokens->content[1] == '\0'))
		{
			write(2, " command not found\n", 20);
			gg()->last_status = 127;
		}
		if (tokens->type == ENV && tokens->content[0] != '$')
		{
			if (tokens && tokens->next)
			{
				tokens = tokens->next;
				exec(tokens, envs);
				return (NULL);
			}
			else
				return (NULL);
		}
		write(2, " command not found\n", 20);
		gg()->last_status = 127;
	}
	return (exec_path);
}

static void	exec_errors(char *exec_path)
{
	if (access(exec_path, F_OK) < 0)
	{
		perror(" ");
		gg()->last_status = 127;
	}
	else if (access(exec_path, X_OK) == 0)
	{
		ft_putstr_fd(" Is a directory\n", 2);
		gg()->last_status = 126;
	}
	else
	{
		gg()->last_status = 126;
		perror(" ");
	}
}

static t_token	*execute_command(char *exec_path,
	char **argv, t_env *envs, t_token *tmp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(exec_path, argv, envs->var) == -1)
			exec_errors(exec_path);
		free_safe(exec_path);
		free_tokens(gg()->token);
		free_envs(gg()->envs);
		clear_history();
		exit(gg()->last_status);
	}
	else if (pid > 0)
	{
		free(exec_path);
		waitpid(pid, &status, 0);
		gg()->last_status = WEXITSTATUS(status);
		return (tmp);
	}
	else
	{
		free(exec_path);
		perror("fork");
		gg()->last_status = 1;
		return (tmp);
	}
}

t_token	*exec_external(t_token *tokens, t_env *envs)
{
	char	**argv;
	char	*exec_path;
	t_token	*tmp;

	argv = build_argv(tokens);
	tmp = tokens;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
	exec_path = get_exec_path(argv, envs, tokens);
	if (!exec_path)
		return (tmp);
	return (execute_command(exec_path, argv, envs, tmp));
}
