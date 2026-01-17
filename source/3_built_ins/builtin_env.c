#include "../../include/builtins.h"

int builtin_env(t_env *env)
{
	t_env *curr;

	curr = env;
	while (curr)
	{
		if (curr->value)
		{
			ft_putstr_fd(curr->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(curr->value, 1);
			ft_putchar_fd('\n', 1);
		}
		curr = curr->next;
	}
	return (0);
}
