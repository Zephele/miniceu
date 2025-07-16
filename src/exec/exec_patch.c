/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_patch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:55:51 by pede-jes          #+#    #+#             */
/*   Updated: 2025/07/16 16:12:32 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../include/minishell.h"

#include "../include/minishell.h"
#include <unistd.h>
#include <sys/wait.h>

static char *get_path_env(char **envp)
{
    int i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
            return envp[i] + 5;
        i++;
    }
    return NULL;
}

static char *find_executable(const char *cmd, char **envp)
{
    char *path_env = get_path_env(envp);
    if (!path_env)
        return NULL;

    char **dirs = ft_split(path_env, ':');
    if (!dirs)
        return NULL;

    char *full_path = NULL;
    int i = 0;
    while (dirs[i])
    {
        char *tmp = ft_strjoin(dirs[i], "/");
        full_path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(full_path, X_OK) == 0)
            break;
        free(full_path);
        full_path = NULL;
        i++;
    }
    ft_free(dirs); // Libera matriz alocada pelo ft_split
    return full_path;
}

static void build_argv(t_token *tokens, char **argv)
{
    int i = 0;
    t_token *tmp = tokens;
    while (tmp && tmp->type != PIPE)
    {
        argv[i++] = tmp->content;
        tmp = tmp->next;
    }
    argv[i] = NULL;
}

t_token *exec_external(t_token *tokens, t_env *envs)
{
    pid_t pid;
    int status;
    char *argv[256];
    char *exec_path;

    build_argv(tokens, argv);

    if (ft_strchr(argv[0], '/'))
        exec_path = ft_strdup(argv[0]);
    else
        exec_path = find_executable(argv[0], envs->var);

    if (!exec_path)
    {
        write(2, "Command not found\n", 18);
        return tokens->next;
    }

    pid = fork();
    if (pid == 0)
    {
        execve(exec_path, argv, envs->var);
        perror("execve");
        free_envs(gg()->envs);
        free_envs(gg()->start_envs);
        exit(127);
    }
    else if (pid > 0)
    {
        free(exec_path);
        waitpid(pid, &status, 0);
        return tokens->next;
    }
    else
    {
        free(exec_path);
        perror("fork");
        return tokens->next;
    }
}