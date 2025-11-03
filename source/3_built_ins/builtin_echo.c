#include "../../include/builtins.h"

static int	is_n_flag(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	builtin_echo(char **args)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = 0;
	while (args[i] && is_n_flag(args[i]))
	{
		no_newline = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
}
