/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pede-jes <pede-jes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:05:11 by pede-jes          #+#    #+#             */
/*   Updated: 2025/08/11 20:18:43 by pede-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../include/minishell.h"

char	*get_path_env(char **envp)
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

static char	*build_full_path(const char *dir, const char *cmd)
{
    char	*tmp;
    char	*full_path;

    tmp = ft_strjoin(dir, "/");
    full_path = ft_strjoin(tmp, cmd);
    free(tmp);
    return (full_path);
}

static char	*search_in_dirs(char **dirs, const char *cmd)
{
    char	*full_path;
    int		i;

    i = 0;
    while (dirs[i])
    {
        full_path = build_full_path(dirs[i], cmd);
        if (access(full_path, X_OK) == 0)
            return (full_path);
        free(full_path);
        i++;
    }
    return (NULL);
}

char	*find_executable(const char *cmd, char **envp)
{
    char	*path_env;
    char	**dirs;
    char	*result;

    path_env = get_path_env(envp);
    if (!path_env)
        return (NULL);
    dirs = ft_split(path_env, ':');
    if (!dirs)
        return (NULL);
    result = search_in_dirs(dirs, cmd);
    ft_free(dirs);
    return (result);
}