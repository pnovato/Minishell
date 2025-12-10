#include "../../include/minishell.h"

int exec_ast(t_node *node, t_env *env_list, int *last_exit)
{	
	//printf("exec_ast: tipo = %d\n", node->type);
	if (!node)
		return (1); //erro generico
	if (node->type == NODE_HEREDOC)
	{
		//printf("Entrou no bloco HEREDOC do exec_ast()\n");
		if (exec_heredoc(node, env_list, last_exit) != 0)
		{
			//printf("exec_heredoc falhou\n");
			return(1);
		}
		//printf("exec_heredoc terminou com sucesso\n");
		t_node *redirect = malloc(sizeof(t_node));
		if (!redirect)
		{
			//printf("malloc do redirect falhou\n");
			return (1);
		}
		//printf("malloc redirect OK\n");
		redirect->type = NODE_LREDIRECT;
		redirect->left = node->left;
		redirect->right = NULL;
		redirect->heredoc_fd = node->heredoc_fd;
		redirect->redirect_file = NULL;
		redirect->av = NULL;
		//printf("redirect pronto: type=%d, fd=%d, comando=%s\n",
		//	redirect->type,
		//	redirect->heredoc_fd,
		//	(redirect->left && redirect->left->av) ? redirect->left->av[0] : "NULO");
		return (exec_ast(redirect, env_list, last_exit));
	}
	if (node->type == NODE_LREDIRECT)
	{
		//printf("Entrou em NODE_LREDIRECT\n");
		return exec_redirect(node, env_list, last_exit);
	}
	if (node->type == NODE_COMMAND)
	{
		//if (!node->av || !node->av[0])
		//	printf("exec_command_node: av vazio\n");
		//else
		//	printf("exec_command_node: primeiro arg = %s\n", node->av[0]);
		return (exec_command_node(node, env_list, last_exit));
	}
	if (node->type == NODE_PIPE)
		return (exec_pipe_node(node, env_list, last_exit));
	if (node->type == NODE_RREDIRECT || node->type == NODE_APPEND)
	{
		//printf("arquivo de redirecionamento: %s\n", node->redirect_file);
		//printf("node: %p | redirect_file = %s\n", (void *)node, node->redirect_file);
		return (exec_redirect(node, env_list, last_exit));
	}
    return (1);
}

int exec_command_node(t_node *node, t_env *env_list, int *last_exit)
{
	pid_t	pid;
	int	status;
	
	if (!node->av || !node->av[0])
        	return (1);
	if (is_builtin(node->av[0]))
	{
		*last_exit = execute_builtin(node->av, env_list);
		return (*last_exit);
	}
    	pid = fork();
    	if (pid == 0)
    	{
		//printf("exec_command_node: av[0] = %s\n", node->av[0]);
		execve(resolve_path(node->av[0], env_list), node->av, env_to_array(env_list));
        	if (node->heredoc_fd > 0)
			dup2(node->heredoc_fd, STDIN_FILENO);
		perror("execve");
		exit(127);
    	}
    	waitpid(pid, &status, 0);
    	//if (WIFEXITED(status))
        *last_exit = WEXITSTATUS(status);
	 return (*last_exit);
}
