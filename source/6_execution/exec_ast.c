#include "../../include/minishell.h"

int exec_ast(t_node *node, t_env *env_list, int *last_exit)
{	
	if (!node)
		return (1);
	if (node->type == NODE_HEREDOC)
		return (exec_heredoc(node, env_list, last_exit));
	if (node->type == NODE_COMMAND)
		return (exec_command_node(node, env_list, last_exit));
	if (node->type == NODE_PIPE)
		return (exec_pipe_node(node, env_list, last_exit));
	if (node->type == NODE_RREDIRECT || node->type == NODE_LREDIRECT)
		return (exec_redirect(node, env_list, last_exit));
    return (1);
}

int	exec_command_node(t_node *node, t_env *env_list, int *last_exit)
{
	pid_t	pid;
	int		status;
	int		err_code;
	char	*path;

	if (is_builtin(node->av[0]))
	{
		*last_exit = execute_builtin(node->av, env_list);
		return (*last_exit);
	}
	
	path = resolve_path(node->av[0], env_list);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->av[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		*last_exit = 127;
		return (127);
	}

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		execve(path, node->av, env_to_array(env_list));
		
		err_code = errno;
		
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->av[0], 2);
		if (err_code == EACCES)
		{
			ft_putstr_fd(": Permission denied\n", 2);
			exit(126);
		}
		else
		{
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(err_code), 2);
			ft_putstr_fd("\n", 2);
			exit(1);
		}
	}
	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid"), 1);
	if (WIFEXITED(status))
		*last_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*last_exit = 128 + WTERMSIG(status);
	free(path);
	return (*last_exit);
}
