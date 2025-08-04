/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pede-jes <pede-jes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:32:46 by pede-jes          #+#    #+#             */
/*   Updated: 2025/08/03 19:10:05 by pede-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_pipes(t_token *tokens)
{
    int		count;
    t_token	*current;

    count = 0;
    current = tokens;
    while (current)
    {
        if (current->type == PIPE)
            count++;
        current = current->next;
    }
    return (count);
}

static t_token	*copy_until_pipe(t_token *start, t_token *end)
{
    t_token	*new_head;
    t_token	*new_current;
    t_token	*current;
    t_token	*new_token;

    new_head = NULL;
    new_current = NULL;
    current = start;
    while (current && current != end)
    {
        new_token = malloc(sizeof(t_token));
        if (!new_token)
            return (NULL);
        new_token->content = ft_strdup(current->content);
        new_token->type = current->type;
        new_token->next = NULL;
        
        if (!new_head)
            new_head = new_token;
        else
            new_current->next = new_token;
        new_current = new_token;
        current = current->next;
    }
    return (new_head);
}

t_token	**split_by_pipes(t_token *tokens)
{
    int		pipe_count;
    t_token	**segments;
    t_token	*current;
    t_token	*segment_start;
    int		i;

    pipe_count = count_pipes(tokens);
    segments = malloc(sizeof(t_token *) * (pipe_count + 2));
    if (!segments)
        return (NULL);
    
    current = tokens;
    segment_start = tokens;
    i = 0;
    
    while (current)
    {
        if (current->type == PIPE)
        {
            segments[i] = copy_until_pipe(segment_start, current);
            i++;
            segment_start = current->next;
        }
        current = current->next;
    }
    segments[i] = copy_until_pipe(segment_start, NULL);
    segments[i + 1] = NULL;
    
    return (segments);
}

void	execute_pipe_segment(t_token *tokens, int input_fd, int output_fd, t_env *envs)
{
    if (input_fd != STDIN_FILENO)
    {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    
    if (output_fd != STDOUT_FILENO)
    {
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);
    }
    if (is_biut(tokens))
    {
        exec_biut(tokens);
        exit(gg()->last_status);
    }
    else
    {
        exec_external(tokens, envs);
        exit(gg()->last_status);
    }
}

t_token	*exec_single_pipe(t_token *left_tokens, t_token *right_tokens, t_env *envs)
{
    int		pipefd[2];
    pid_t	pid1, pid2;
    int		status;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return (NULL);
    }

    pid1 = fork();
    if (pid1 == 0)
    {
        close(pipefd[0]);
        execute_pipe_segment(left_tokens, STDIN_FILENO, pipefd[1], envs);
    }

    pid2 = fork();
    if (pid2 == 0)
    {
        close(pipefd[1]);
        execute_pipe_segment(right_tokens, pipefd[0], STDOUT_FILENO, envs);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);
    gg()->last_status = WEXITSTATUS(status);

    return (NULL);
}

static void	create_pipes(int **pipes, int pipe_count)
{
    int	i;

    i = 0;
    while (i < pipe_count)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            return ;
        }
        i++;
    }
}

static void	close_all_pipes(int **pipes, int pipe_count)
{
    int	j;

    j = 0;
    while (j < pipe_count)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
        j++;
    }
}

static void	setup_child_process(int **pipes, int pipe_count, int i)
{
    if (i > 0)
        dup2(pipes[i - 1][0], STDIN_FILENO);
    
    if (i < pipe_count)
        dup2(pipes[i][1], STDOUT_FILENO);
    
    close_all_pipes(pipes, pipe_count);
}

static void	create_child_processes(t_token **segments, int **pipes, pid_t *pids, t_env *envs)
{
    int	pipe_count;
    int	i;
    
    i = 0;
    pipe_count = 0;
    while (segments[pipe_count])
        pipe_count++;
    pipe_count--;
    
    while (i <= pipe_count)
    {
        pids[i] = fork();
        if (pids[i] == 0)
        {
            setup_child_process(pipes, pipe_count, i);
            
            if (is_biut(segments[i]))
            {
                exec_biut(segments[i]);
                exit(gg()->last_status);
            }
            else
            {
                exec_external(segments[i], envs);
                exit(gg()->last_status);
            }
        }
        i++;
    }
}

static void	wait_all_processes(pid_t *pids, int pipe_count)
{
    int	status;
    int	i;

    i = 0;
    while (i <= pipe_count)
    {
        waitpid(pids[i], &status, 0);
        if (i == pipe_count)
            gg()->last_status = WEXITSTATUS(status);
        i++;
    }
}

static void	free_pipes_memory(int **pipes, int pipe_count)
{
    int	i;

    i = 0;
    while (i < pipe_count)
    {
        free(pipes[i]);
        i++;
    }
    free(pipes);
}

static void	free_segments_memory(t_token **segments)
{
    int	i;

    i = 0;
    while (segments[i])
    {
        free_tokens(segments[i]);
        i++;
    }
    free(segments);
}

t_token	*exec_multiple_pipes(t_token *tokens, t_env *envs)
{
    int		pipe_count;
    t_token	**segments;
    int		**pipes;
    pid_t	*pids;

    pipe_count = count_pipes(tokens);
    if (pipe_count == 0)
        return (handle_redirects(&tokens));

    segments = split_by_pipes(tokens);
    if (!segments)
        return (NULL);
    
    pipes = malloc(sizeof(int *) * pipe_count);
    create_pipes(pipes, pipe_count);
    
    pids = malloc(sizeof(pid_t) * (pipe_count + 1));
    create_child_processes(segments, pipes, pids, envs);
    
    close_all_pipes(pipes, pipe_count);
    wait_all_processes(pids, pipe_count);
    
    free_pipes_memory(pipes, pipe_count);
    free(pids);
    free_segments_memory(segments);

    return (NULL);
}

t_token	*handle_pipes(t_token *tokens, t_env *envs)
{
    int		pipe_count;
    t_token	**segments;
    t_token	*result;

    if (!tokens)
        return (NULL);

    pipe_count = count_pipes(tokens);
    
    if (pipe_count == 0)
        return (handle_redirects(&tokens));
    else if (pipe_count == 1)
    {
        segments = split_by_pipes(tokens);
        result = exec_single_pipe(segments[0], segments[1], envs);
        free_tokens(segments[0]);
        free_tokens(segments[1]);
        free(segments);
        return (result);
    }
    else
        return (exec_multiple_pipes(tokens, envs));
}