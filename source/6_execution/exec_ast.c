#include "../../include/minishell.h"

int exec_command_node(t_node *node, t_shell *sh, int *last_exit, int in_child)
{
	if (!node->av || !node->av[0])
		return (1);
	if (is_builtin(node->av[0]))
		return (run_builtin(node, sh, last_exit, in_child));
	if (in_child)
		execve_or_die(node, sh, resolve_path(node->av[0], sh->env));
	return (exec_external_cmd(node, sh, last_exit));
}

int exec_ast(t_node *node, t_shell *sh, int *last_exit, int in_child)
{
	if (!node)
		return (1);
	if (is_empty_cmd(node))
		return (*last_exit = 0);
	if (node->type == NODE_HEREDOC)
		return (exec_ast_heredoc_node(node, sh, last_exit, in_child));
	if (node->type == NODE_COMMAND)
		return (exec_command_node(node, sh, last_exit, in_child));
	if (node->type == NODE_PIPE)
		return (exec_pipe_node(node, sh, last_exit));
	if (node->type == NODE_LREDIRECT || node->type == NODE_RREDIRECT || node->type == NODE_APPEND)
		return (exec_redirect(node, sh, last_exit, in_child));
	return (exec_unsupported_in_child(in_child, last_exit));
}

t_node *copy_ast(t_node *node)
{
	t_node *new;

	if (!node)
		return (NULL);
	new = alloc_copy_node(node);
	if (!new)
		return (NULL);
	if (node->av)
	{
		new->av = dup_av(node->av);
		if (!new->av)
			return (free_ast(new), NULL);
		return (new);
	}
	new->left = copy_ast(node->left);
	new->right = copy_ast(node->right);
	return (new);
}

void close_fds_from(int start)
{
	int fd;

	fd = start;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}