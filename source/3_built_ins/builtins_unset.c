#include "../../include/builtins.h"

void	builtin_unset(char **args, t_env *env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env_var(&env, args[i]);
		i++;
	}
}
