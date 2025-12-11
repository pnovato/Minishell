#include "../../include/minishell.h"

int	exec_redirect(t_node *node, t_env *env_list, int *last_exit, int in_child)
{
	int		fd;
	int		saved_stdin = -1;
	int		saved_stdout = -1;

	if (!node || !node->left)
		return (*last_exit = 1);

	if (node->heredoc_fd > 0)
		fd = node->heredoc_fd;
	else if (node->type == NODE_RREDIRECT)
		fd = open(node->redirect_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->type == NODE_LREDIRECT)
		fd = open(node->redirect_file, O_RDONLY);
	else if (node->type == NODE_APPEND)
		fd = open(node->redirect_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (*last_exit = 1);

	if (fd < 0)
		return (perror("open"), *last_exit = 1);

	if (!in_child)
	{
		if (node->type == NODE_LREDIRECT || node->heredoc_fd > 0)
			saved_stdin = dup(STDIN_FILENO);
		else
			saved_stdout = dup(STDOUT_FILENO);
	}

	if (node->type == NODE_LREDIRECT || node->heredoc_fd > 0)
	{
		//printf("[redirect] dup2(fd=%d) → STDIN\n", fd);
		dup2(fd, STDIN_FILENO);
	}
	else
	{
		//printf("[redirect] dup2(fd=%d) → STDOUT\n", fd);
		dup2(fd, STDOUT_FILENO);
	}

	close(fd);

	//printf("[redirect] chamando exec_ast dentro do redirect (in_child = %d)\n", in_child);
	int code = exec_ast(node->left, env_list, last_exit, in_child);
	//printf("[redirect] exec_ast retornou code = %d\n", code);

	if (!in_child)
	{
		if (saved_stdin != -1)
		{
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
		}
		if (saved_stdout != -1)
		{
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdout);
		}
	}

	if (in_child)
	{
		//printf("[redirect] in_child = 1 → exit(%d)\n", code);
		exit(code);
	}
	//printf("[redirect] in_child = 0 → return %d\n", code);
	return (code);
}

