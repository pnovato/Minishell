#include "../../include/minishell.h"

static void run_left_child(t_node *node, t_shell *sh, int *last_exit, int *p)
{
	int code;

	close(p[0]);
	dup2(p[1], STDOUT_FILENO);
	close(p[1]);
	setup_signals_child();
	code = exec_ast(node->left, sh, last_exit, 1);
	cleanup_child(sh);
	close_fds_from(3);
	_exit(code);
}

static void run_right_child(t_node *node, t_shell *sh, int *last_exit, int *p)
{
	int code;

	close(p[1]);
	dup2(p[0], STDIN_FILENO);
	close(p[0]);
	setup_signals_child();
	code = exec_ast(node->right, sh, last_exit, 1);
	cleanup_child(sh);
	close_fds_from(3);
	_exit(code);
}

static int wait_pipe_children(pid_t left, pid_t right, int *last_exit)
{
	int left_status;
	int right_status;

	waitpid(left, &left_status, 0);
	waitpid(right, &right_status, 0);
	if (WIFEXITED(right_status))
		*last_exit = WEXITSTATUS(right_status);
	else
		*last_exit = 1;
	return (*last_exit);
}

int exec_pipe_node(t_node *node, t_shell *sh, int *last_exit)
{
	int pipefd[2];
	pid_t left;
	pid_t right;

	if (!node->left)
		return (*last_exit = 1);
	if (pipe(pipefd) < 0)
		return (perror("pipe"), *last_exit = 1);
	left = fork();
	if (left == 0)
		run_left_child(node, sh, last_exit, pipefd);
	right = fork();
	if (right == 0)
		run_right_child(node, sh, last_exit, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	return (wait_pipe_children(left, right, last_exit));
}
