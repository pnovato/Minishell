#include "../../include/builtins.h"

static int is_numeric(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void exit_with_cleanup(t_shell *sh, int code)
{
	cleanup_child(sh);
	exit(code);
}

int builtin_exit(t_shell *sh, char **args)
{
	int exit_code;

	ft_putstr_fd("exit\n", 2);
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit_with_cleanup(sh, 255);
		}
		if (args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		exit_code = ft_atoi(args[1]) % 256;
		exit_with_cleanup(sh, (int)(exit_code % 256));
	}
	exit_with_cleanup(sh, 0);
	return (0);
}
