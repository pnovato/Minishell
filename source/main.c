#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	minishell_loop(t_env *env_list, int last_exit)
{
	char	*expanded;
	char	*input;

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
		handle_the_inputs(input, env_list);
		split_line_to_token();
		expanded = expand_env_variables(input, env_list, last_exit);		
		free(input);
		free(expanded);
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

void	print_token_list(t_list *token)
{
	while (token)
	{
		printf("%s\n", (char *)token->content);
			token = token->next;
	}
}

int main(int ac, char **av, char **envp)
{
	t_env	*env_list;
	int	last_exit = 42;
	(void)ac;
	(void)av;
	env_list = envp_to_list(envp);
	minishell_loop(env_list, last_exit); 
	free_env_list(env_list);
	return (0);
}

