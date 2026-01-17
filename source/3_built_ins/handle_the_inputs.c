#include "../../include/builtins.h"

int execute_builtin(char **args, t_env *env, t_shell *sh)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, env));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(sh, args));
	else if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(env));
	else if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, env));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, env));
	return (1);
}
