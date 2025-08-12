/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pede-jes <pede-jes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:21:27 by pede-jes          #+#    #+#             */
/*   Updated: 2025/08/11 20:23:52 by pede-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../include/minishell.h"

static char	**build_argv(t_token *tokens)
{
    static char	*argv[256];
    t_token		*tmp;
    int			i;

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

static char	*get_exec_path(char **argv, t_env *envs)
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
    }
    return (exec_path);
}

static t_token	*execute_command(char *exec_path, char **argv, t_env *envs, t_token *tmp)
{
    pid_t	pid;
    int		status;

    pid = fork();
    if (pid == 0)
    {
        execve(exec_path, argv, envs->var);
        perror("execve");
        exit(127);
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

    exec_path = get_exec_path(argv, envs);
    if (!exec_path)
        return (tmp);

    return (execute_command(exec_path, argv, envs, tmp));
}