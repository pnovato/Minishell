#include "../../include/builtins.h"

void builtin_export(char **args, t_env *env)
{
	int		i;
	char	*eq;
	char	*key;
	char	*value;

	i = 1;
	while (args[i])
	{
		eq = ft_strchr(args[i], '=');
		if (!eq)
		{
			ft_putendl_fd("export: invalid format", 2);
			i++;
			continue ;
		}
		key = ft_substr(args[i], 0, eq - args[i]);
		value = ft_strdup(eq + 1);
		update_env_value(&env, key, value);
		free(key);
		free(value);
		i++;
	}
}
