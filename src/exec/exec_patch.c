/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_patch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:55:51 by pede-jes          #+#    #+#             */
/*   Updated: 2025/08/05 19:36:10 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../include/minishell.h"

#include "../include/minishell.h"
#include <unistd.h>
#include <sys/wait.h>

static char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*find_executable(const char *cmd, char **envp)
{
	char	*path_env;
	char	**dirs;
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	full_path = NULL;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
		i++;
	}
	ft_free(dirs);
	return (full_path);
}

t_token	*exec_external(t_token *tokens, t_env *envs)
{
	pid_t pid;
	int status;
	char *argv[256];
	char *exec_path;
	t_token *tmp = tokens;
	int 	i;

	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		tmp->content = no_quotes(tmp->content);
		argv[i++] = tmp->content;
		tmp = tmp->next;
	}
	argv[i] = NULL;

	if (ft_strchr(argv[0], '/'))
		exec_path = ft_strdup(argv[0]);
	else
		exec_path = find_executable(argv[0], envs->var);

	if (!exec_path)
	{
		write(2, "Command not found\n", 18);
		gg()->last_status = 127;
		return tmp;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(exec_path, argv, envs->var);
		perror("execve");
		free_envs(gg()->envs);
		exit(127);
	}
	else if (pid > 0)
	{
		free(exec_path);
		waitpid(pid, &status, 0);
		gg()->last_status = WEXITSTATUS(status);
		return tmp;
	}
	else
	{
		free(exec_path);
		perror("fork");
		gg()->last_status = 1;
		return tmp;
	}
}

void exec_external_with_argv(char **argv, t_env *envs)
{
    pid_t pid;
    int status;
    char *exec_path;

    if (ft_strchr(argv[0], '/'))
        exec_path = ft_strdup(argv[0]);
    else
        exec_path = find_executable(argv[0], envs->var);

    if (!exec_path)
    {
        write(2, "Command not found\n", 18);
        gg()->last_status = 127;
        return;
    }

    pid = fork();
    if (pid == 0)
    {
        execve(exec_path, argv, envs->var);
        perror("execve");
        free_envs(gg()->envs);
        exit(127);
    }
    else if (pid > 0)
    {
        free(exec_path);
        waitpid(pid, &status, 0);
        gg()->last_status = WEXITSTATUS(status);
    }
    else
    {
        free(exec_path);
        perror("fork");
        gg()->last_status = 1;
    }
}
