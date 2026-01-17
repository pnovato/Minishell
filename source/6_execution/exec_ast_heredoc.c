#include "../../include/minishell.h"

int exec_heredoc(t_node *node, t_shell *sh, int *last_exit)
{
	int pipe_fd[2];
	pid_t pid;

	if (pipe(pipe_fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), 1);
	if (pid == 0)
		run_heredoc_child(node, sh, pipe_fd, *last_exit);
	close(pipe_fd[1]);
	if (heredoc_wait_parent(pid, pipe_fd[0], last_exit))
		return (1);
	node->heredoc_fd = pipe_fd[0];
	node->type = NODE_LREDIRECT;
	return (0);
}

int resolve_heredocs(t_node *node, t_shell *sh, int *last_exit)
{
	if (!node)
		return (0);
	if (node->type == NODE_HEREDOC)
	{
		if (exec_heredoc(node, sh, last_exit))
			return (*last_exit = 130, 1);
		if (transform_heredoc_node(node))
			return (1);
	}
	if (resolve_heredocs(node->left, sh, last_exit))
		return (1);
	if (resolve_heredocs(node->right, sh, last_exit))
		return (1);
	return (0);
}

void assert_tree_no_heredocs(t_node *node)
{
	if (!node)
		return;
	if (node->type == NODE_HEREDOC)
	{
		perror("Heredoc node found after resolution");
		exit(1);
	}
	assert_tree_no_heredocs(node->left);
	assert_tree_no_heredocs(node->right);
}

void cleanup_child(t_shell *sh)
{
	if (!sh)
		return;
	close_if_valid(&sh->stdin_bkp);
	close_if_valid(&sh->stdout_bkp);
	close_if_valid(&sh->stderr_bkp);
	free_line(&sh->line);
	free_tokens(&sh->tokens);
	free_ast_ptr(&sh->ast);
	free_env_ptr(&sh->env);
}

void cleanup_child_min(t_node *ast, t_token *tokens, t_env *env, char *line)
{
	if (line)
		free(line);
	if (tokens)
		free_token_list(tokens);
	if (ast)
		free_ast(ast);
	if (env)
		free_env_list(env);
}
