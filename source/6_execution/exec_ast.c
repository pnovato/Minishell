#include "../../include/minishell.h"

int exec_ast(t_node *node, t_env *env_list, int *last_exit, int in_child)
{	
	//printf("exec_ast: tipo = %d\n", node->type);
	if (!node)
		return (1); //erro generico
	if (node->type == NODE_COMMAND && (!node->av || !node->av[0]))
	{
		//printf("Comando vazio ignorado\n");
		return (*last_exit = 0);
	}
	if (node->type == NODE_HEREDOC)
	{
		//printf("Entrou no bloco HEREDOC do exec_ast()\n");
		//printf("[exec_ast] tipo = %d | in_child = %d\n", node->type, in_child);
		
		if (in_child)
		{
			fprintf(stderr, "Erro: HEREDOC não deve ser executado em processo filho.\n");
			exit(1);
		}
		if (exec_heredoc(node, env_list, last_exit) != 0)
		{
			//printf("exec_heredoc falhou\n");
			return(1);
		}
		//printf("exec_heredoc terminou com sucesso\n");
		t_node *old_left = node->left;

		if (node->left && node->left->type == NODE_HEREDOC)
			node->left->type = NODE_LREDIRECT;
		node->type = NODE_LREDIRECT;
		node->left = copy_ast(old_left);  // cria nova subárvore segura para usar nos filhos
		node->right = NULL;
		node->redirect_file = NULL;
		node->av = NULL;
		int result = exec_ast(node, env_list, last_exit, in_child);
		free_ast(old_left);
		return result;
	}
	if (node->type == NODE_LREDIRECT)
	{
		//printf("Entrou em NODE_LREDIRECT\n");
		//printf("[exec_ast] tipo = %d | in_child = %d\n", node->type, in_child);
		return exec_redirect(node, env_list, last_exit, in_child);
	}
	if (node->type == NODE_COMMAND)
	{
		//printf("[exec_ast] comando = %s | tipo = %d | in_child = %d\n",
       //(node->av && node->av[0]) ? node->av[0] : "NULL", node->type, in_child);	
		return (exec_command_node(node, env_list, last_exit, in_child));
	}
	if (node->type == NODE_PIPE)
	{
		//printf("[exec_ast] tipo = %d | in_child = %d\n", node->type, in_child);
		return (exec_pipe_node(node, env_list, last_exit));
	}
	if (node->type == NODE_RREDIRECT || node->type == NODE_APPEND)
	{
		//printf("arquivo de redirecionamento: %s\n", node->redirect_file);
		//printf("node: %p | redirect_file = %s\n", (void *)node, node->redirect_file);
		//printf("[exec_ast] tipo = %d | in_child = %d\n", node->type, in_child);
		return (exec_redirect(node, env_list, last_exit, in_child));
	}
	if (in_child)
		exit(*last_exit);
	return (*last_exit);
}

int exec_command_node(t_node *node, t_env *env_list, int *last_exit, int in_child)
{
	pid_t	pid;
	int	status;

	//printf("[exec_command_node] comando = %s | in_child = %d\n", node->av[0], in_child);	
	if (!node->av || !node->av[0])
        	return (1);
	if (is_builtin(node->av[0]))
	{
		*last_exit = execute_builtin(node->av, env_list);
		return (*last_exit);
	}
	if (in_child)
	{
		//printf("[exec_command_node] EXECVE direto: %s\n", node->av[0]);
		if (node->heredoc_fd > 0)
			dup2(node->heredoc_fd, STDIN_FILENO);
		char **envp = env_to_array(env_list);
		/*int i = 0;
		printf("ENVIRONMENTO PARA EXECVE:\n");
		while (envp && envp[i])
		{
			printf("  envp[%d] = %s\n", i, envp[i]);
			i++;
		}*/

		execve(resolve_path(node->av[0], env_list), node->av, envp);
		perror("execve");
		exit(127);
	}
    	pid = fork();
    	if (pid == 0)
    	{
		//printf("[exec_command_node] EXECVE com fork: %s\n", node->av[0]);
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

t_node *copy_ast(t_node *node)
{
	if (!node)
		return NULL;

	t_node *new = malloc(sizeof(t_node));
	if (!new)
		return NULL;

	memset(new, 0, sizeof(t_node));

	new->type = node->type;
	new->heredoc_fd = node->heredoc_fd;
	new->redirect_file = node->redirect_file ? ft_strdup(node->redirect_file) : NULL;

	// Copiar av (array de strings)
	if (node->av)
	{
		int i = 0;
		while (node->av[i])
			i++;
		new->av = malloc(sizeof(char *) * (i + 1));
		if (!new->av)
		{
			free(new);
			return NULL;
		}
		for (int j = 0; j < i; j++)
		new->av[j] = ft_strdup(node->av[j]);
		new->av[i] = NULL;
	}	
	else
	new->av = NULL;
	// Recursivamente duplicar filhos
	new->left = copy_ast(node->left);
	new->right = copy_ast(node->right);
	return new;
}

