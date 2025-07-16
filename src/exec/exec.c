#include "../include/minishell.h"

static int is_biut(t_token *tokens)
{
    if (!tokens || !tokens->content)
        return (0);
    if (compare_aux(tokens->content, "echo") == 0
        || compare_aux(tokens->content, "cd") == 0
        || compare_aux(tokens->content, "exit") == 0
        || compare_aux(tokens->content, "env") == 0
        || compare_aux(tokens->content, "unset") == 0
        || compare_aux(tokens->content, "export") == 0
        || compare_aux(tokens->content, "pwd") == 0)
        return (1);
    return (0);
}


static t_token *exec_biut(t_token *tokens)
{
    if (compare_aux(tokens->content, "echo") == 0)
        return ft_echo(&tokens);
    else if (compare_aux(tokens->content, "cd") == 0)
        return ft_cd(&tokens);
    else if (compare_aux(tokens->content, "exit") == 0)
    {
        ft_exit(&tokens);
        return NULL;
    }
    else if (compare_aux(tokens->content, "env") == 0)
        return ft_env(&tokens);
    else if (compare_aux(tokens->content, "export") == 0)
        return ft_export(&tokens);
    else if (compare_aux(tokens->content, "unset") == 0)
        return ft_unset(&tokens);
    else if (compare_aux(tokens->content, "pwd") == 0)
        return ft_pwd(&tokens);
    return tokens->next;
}

t_token *exec(t_token *tokens, t_env *envs)
{
    if (is_biut(tokens))
        return exec_biut(tokens);
    else
    {
        exec_external(tokens, envs);
        return tokens->next;
    }
}
