#include"../include/minishell.h"

void	print_env_list(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

int main(int ac, char **av, char **envp)
{
	t_env	*env_list;
	char	*line;
	char	*expanded;
	int	last_exit = 42;
	(void)ac;
	(void)av;
	env_list = envp_to_list(envp);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (*line)
			add_history(line);
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}
		expanded = expand_env_variables(line, env_list, last_exit);
		printf("expandido: %s\n", expanded);
		free(expanded);
		free(line);
	}
	//free_env_list(env_list);
	return (0);
}

