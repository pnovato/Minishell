#include "../../include/minishell.h"

t_env	*create_env_node(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		free(new);
		return (NULL);
	}
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	free_env_list(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = temp;	
	}
}

void	free_token_list(t_token *token)
{
	t_token	*temp;
	while (token)
	{
		temp = token->next;
		free(token->value);
		free(token);
		token = temp;
	}
}
