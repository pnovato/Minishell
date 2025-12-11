#include "../../include/minishell.h"

int	exec_pipe_node(t_node *node, t_env *env_list, int *last_exit)
{
	int	pipefd[2];
	//int	status;
	int	left_status;
	int	right_status;
	pid_t	left;
	pid_t	right;
	
	if (!node->left)
		return (*last_exit = 1);
	if (pipe(pipefd) < 0)
		return (perror("pipe"), *last_exit = 1);
	pipe(pipefd);
	left = fork();
	if (left == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		int code = exec_ast(node->left, env_list, last_exit, 1);
		exit(code);
	}
	right = fork();
	if (right == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		int code = exec_ast(node->right, env_list, last_exit, 1);
		exit(code);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(left, &left_status, 0);
	waitpid(right, &right_status, 0);
	if (WIFEXITED(right_status))
		*last_exit = WEXITSTATUS(right_status);
	else
		*last_exit = 1;
	return (*last_exit);
}

