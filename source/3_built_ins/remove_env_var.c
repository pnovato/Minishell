#include "../../include/builtins.h"

void	remove_env_var(t_env **env, const char *key)
{
	t_env *prev = NULL;
	t_env *curr = *env;

	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
