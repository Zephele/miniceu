/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_patch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pede-jes <pede-jes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:55:51 by pede-jes          #+#    #+#             */
/*   Updated: 2025/08/11 20:22:43 by pede-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../include/minishell.h"

static char	*get_executable_path(char **argv, t_env *envs)
{
    char	*exec_path;

    if (ft_strchr(argv[0], '/'))
        exec_path = ft_strdup(argv[0]);
    else
        exec_path = find_executable(argv[0], envs->var);

    if (!exec_path)
    {
        write(2, "Command not found\n", 18);
        gg()->last_status = 127;
        return (NULL);
    }
    return (exec_path);
}

static void	execute_child_command(char *exec_path, char **argv, t_env *envs)
{
    execve(exec_path, argv, envs->var);
    perror("execve");
    exit(127);
}

static void	handle_parent_process(char *exec_path, pid_t pid)
{
    int	status;

    free(exec_path);
    waitpid(pid, &status, 0);
    gg()->last_status = WEXITSTATUS(status);
}

void exec_external_with_argv(char **argv, t_env *envs)
{
    pid_t	pid;
    char	*exec_path;

    exec_path = get_executable_path(argv, envs);
    if (!exec_path)
        return;

    pid = fork();
    if (pid == 0)
        execute_child_command(exec_path, argv, envs);
    else if (pid > 0)
        handle_parent_process(exec_path, pid);
    else
    {
        free(exec_path);
        perror("fork");
        gg()->last_status = 1;
    }
}
