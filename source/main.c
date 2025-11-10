#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	minishell_loop(t_env *env_list, int *last_exit)
{
	char	*input;
	char	**args;
	t_token	*token;
	t_node	*ast;

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
		token = split_line_to_token(input);
		expand_token_list(token, env_list, *last_exit);
		//print_token_list(token);
		remove_token_quotes(token);
		if (has_operator(token))
		{
			ast = build_ast(token, ft_lstlast_token(token));
			if (ast)
			{	
				*last_exit = exec_ast(ast, env_list, last_exit);
				free_ast(ast); //adicionar esta funcao, para liberar memoria recursivamente
			}
			else
				printf("erro na AST\n");
		}
		else
		{
			args = token_list_to_args(token);
			handle_the_inputs(args, env_list, last_exit);
			free_split(args);
		}		
		free_token_list(token);
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

void	print_token_list(t_token *token)
{
	while (token)
	{
		printf("Token: [%s] -> Tipo: [%d]\n", token->raw_value, token->type);
		token = token->next;
	}
}

void print_ast(t_node *node, int depth)
{
	if (!node)
		return;

	for (int i = 0; i < depth; i++)
		printf(" ");
	if (node->type == NODE_COMMAND)
	{
		printf("[%s]", node_type_str(node->type));
		if (node->av)
		{
			for (int i = 0; node->av[i]; i++)
				printf(" %s", node->av[i]);
		}
		printf("\n");
	}
	else
		printf("[%s]\n", node_type_str(node->type));
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}

int main(int ac, char **av, char **envp)
{
	t_env	*env_list;
	int	last_exit = 42;
	(void)ac;
	(void)av;
	env_list = envp_to_list(envp);
	minishell_loop(env_list, &last_exit); 
	free_env_list(env_list);
	return (0);
}

