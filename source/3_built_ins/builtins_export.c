#include "../../include/builtins.h"

static int is_valid_export_key(char *key)
{
	int i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int builtin_export(char **args, t_env *env)
{
	int i;
	int exit_code;
	char *eq;
	char *key;

	i = 1;
	exit_code = 0;
	if (!args[1])
		return export_print(env);
	while (args[i])
	{
		eq = ft_strchr(args[i], '=');
		if (eq)
			key = ft_substr(args[i], 0, eq - args[i]);
		else
			key = ft_strdup(args[i]);
		if (!is_valid_export_key(key))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_code = 1;
		}
		else if (eq)
			update_env_value(&env, key, eq + 1);
		free(key);
		i++;
	}
	return (exit_code);
}

int export_print(t_env *env)
{
	t_env *cur = env;

	while (cur)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (cur->key)
			ft_putstr_fd(cur->key, STDOUT_FILENO);
		if (cur->value)
		{
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(cur->value, STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		cur = cur->next;
	}
	return (0);
}
