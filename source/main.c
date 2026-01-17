#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int g_signal_status = 0;

static int handle_exit_line(char *input)
{
	if (!input)
	{
		printf("exit\n");
		return (1);
	}
	if (ft_strcmp(input, "exit") == 0)
		return (1);
	return (0);
}

static void init_shell(t_shell *sh, t_env *env, t_token *tok, t_node *ast)
{
	sh->ast = ast;
	sh->tokens = tok;
	sh->env = env;
	sh->line = NULL;
	sh->stdin_bkp = -1;
	sh->stdout_bkp = -1;
	sh->stderr_bkp = -1;
}

static int exec_one_line(t_env *env, int *last_exit, char *input)
{
	t_token *tok;
	t_node *ast;
	t_shell sh;

	tok = split_line_to_token(input);
	if (!tok)
		return (free(input), 0);
	expand_token_list(tok, env, *last_exit);
	remove_token_quotes(tok);
	ast = build_ast(tok, ft_lstlast_token(tok));
	if (!ast)
		return (free_token_list(tok), free(input), 0);
	init_shell(&sh, env, tok, ast);
	sh.line = input;
	if (resolve_heredocs(ast, &sh, last_exit))
		return (g_signal_status = 0, free_ast(ast),
				free_token_list(tok), free(input), 0);
	assert_tree_no_heredocs(ast);
	*last_exit = exec_ast(ast, &sh, last_exit, 0);
	free_ast(ast);
	free_token_list(tok);
	free(input);
	return (0);
}

void minishell_loop(t_env *env_list, int *last_exit)
{
	char *input;

	while (1)
	{
		setup_signals_main();
		if (g_signal_status == 130)
			g_signal_status = 0;
		rl_on_new_line();
		input = readline("minishell$ ");
		if (handle_exit_line(input))
		{
			if (input)
				free(input);
			break;
		}
		if (*input)
			add_history(input);
		exec_one_line(env_list, last_exit, input);
	}
}

int main(int ac, char **av, char **envp)
{
	t_env *env_list;
	int last_exit = 42;
	(void)ac;
	(void)av;
	env_list = envp_to_list(envp);
	minishell_loop(env_list, &last_exit);
	free_env_list(env_list);
	return (0);
}
