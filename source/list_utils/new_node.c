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

void	free_ast(t_node *node)
{
	int	i;
	
	if (!node)
		return;
	if (node->av)
	{
		i = 0;
		while (node->av[i])
		{
			free(node->av[i]);
			i++;
		}
		free(node->av);
	}
	if (node->redirect_file)
		free(node->redirect_file);
	free_ast(node->left);	
	free_ast(node->right);
	free(node);
}
