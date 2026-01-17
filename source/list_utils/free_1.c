#include "../../include/minishell.h"

void free_env_list(t_env *env)
{
    t_env *temp;

    while (env)
    {
        temp = env->next;
        free(env->key);
        free(env->value);
        free(env);
        env = temp;
    }
}

void free_env_ptr(t_env **env)
{
    if (!env || !*env)
        return;
    free_env_list(*env);
    *env = NULL;
}

void free_token(t_token *t)
{
    if (!t)
        return;
    free(t->value);
    free(t->raw_value);
    free(t);
}

void free_tokens(t_token **tokens)
{
    if (!tokens || !*tokens)
        return;
    free_token_list(*tokens);
    *tokens = NULL;
}

void free_token_list(t_token *token)
{
    t_token *temp;
    while (token)
    {
        temp = token->next;
        free_token(token);
        token = temp;
    }
}