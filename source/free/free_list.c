#include "../../include/minishell.h"

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
