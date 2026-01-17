#include "../../include/minishell.h"

char **env_to_array(t_env *env)
{
	int count;
	char **envp;
	int i;

	count = env_size(env);
	envp = malloc(sizeof(char *) * (count + 1));
	i = 0;
	if (!envp)
		return (NULL);
	while (env)
	{
		envp[i++] = join_key_value(env->key, env->value);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
