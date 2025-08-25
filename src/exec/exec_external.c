/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:21:27 by pede-jes          #+#    #+#             */
/*   Updated: 2025/08/25 17:49:50 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**build_argv(t_token *tokens)
{
	static char	*argv[256];
	t_token		*tmp;
	int			i;

	tmp = tokens;
	i = 0;
	while (tmp && tmp->content && tmp->type != PIPE)
	{
		tmp->content = no_quotes(tmp->content);
		argv[i++] = tmp->content;
		if (tmp->next && tmp->next->content)
			tmp = tmp->next;
		else
			break ;
	}
	argv[i] = NULL;
	return (argv);
}

static void	*env_exec(t_env *envs, t_token *tokens)
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

static char	*get_exec_path(char **argv, t_env *envs, t_token *tokens)
{
	char	*exec_path;

	if (argv[0])
	{
		if (ft_strchr(argv[0], '/'))
			exec_path = ft_strdup(argv[0]);
		else
			exec_path = find_executable(argv[0], envs->var);
	}
	else
	{
		gg()->last_status = 127;
		return (NULL);
	}
	if (!exec_path)
	{
		if (!get_exec_aux(tokens))
			return (NULL);
		if (tokens->type == ENV && tokens->content[0] != '$')
			return (env_exec(envs, tokens));
		write(2, "Command not found\n", 19);
		gg()->last_status = 127;
	}
	return (exec_path);
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
		free_exec(exec_path);
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
	setup_prompt_functions();
	return (execute_command(exec_path, argv, envs, tmp));
}
