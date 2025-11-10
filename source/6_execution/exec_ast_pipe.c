#include "../../include/minishell.h"

int	exec_pipe_node(t_node *node, t_env *env_list, int *last_exit)
{
	int	pipefd[2];
	int	status;	
	pid_t	left;
	pid_t	right;

	pipe(pipefd);
	left = fork();
	if (left == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exit(exec_ast(node->left, env_list, last_exit));
	}
	right = fork();
	if (right == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exit(exec_ast(node->right, env_list, last_exit));
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(left, &status, 0);
	waitpid(right, &status, 0);
	if (WIFEXITED(status))
		*last_exit = WIFEXITED(status);
	return (*last_exit);
}
