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
