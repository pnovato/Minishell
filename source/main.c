#include"../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	minishell_loop(t_env *env_list)
{
	char	*input;

	(void)env_list;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		free(input);
	}
}

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
	(void)ac;
	(void)av;
	env_list = envp_to_list(envp);
	if(!env_list)
	{
		printf("Erro ao criar env_list.\n");
		return (1);
	}
	minishell_loop(env_list);
	print_env_list(env_list);
	return (0);
}

