#include "../../include/minishell.h"

int	exec_redirect(t_node *node, t_env *env_list, int *last_exit)
{
	int		fd;
	pid_t	pid;
	int		status;

	if (!node || !node->left || !node->redirect_file)
	{
		*last_exit = 1;
		return (1);
	}

	// 1) Abrir o ficheiro de acordo com o tipo de redirecionamento
	if (node->type == NODE_RREDIRECT)          // comando > ficheiro
		fd = open(node->redirect_file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->type == NODE_LREDIRECT)     // comando < ficheiro
		fd = open(node->redirect_file, O_RDONLY);
	else
	{
		*last_exit = 1;
		return (1);
	}

	if (fd < 0)
	{
		perror("open");
		*last_exit = 1;
		return (1);
	}

	// 2) Criar processo filho para executar o comando com FDs redirecionados
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(fd);
		*last_exit = 1;
		return (1);
	}
	if (pid == 0)
	{
		// --- FILHO ---
		if (node->type == NODE_RREDIRECT)
		{
			if (dup2(fd, STDOUT_FILENO) < 0)
			{
				perror("dup2");
				exit(1);
			}
		}
		else if (node->type == NODE_LREDIRECT)
		{
			if (dup2(fd, STDIN_FILENO) < 0)
			{
				perror("dup2");
				exit(1);
			}
		}
		close(fd);

		// Executar o comando que está na esquerda do redirecionamento
		if (!node->left->av || !node->left->av[0])
			exit(0);

		if (is_builtin(node->left->av[0]))
		{
			execute_builtin(node->left->av, env_list);
			exit(0);
		}
		execve(resolve_path(node->left->av[0], env_list),
			node->left->av,
			env_to_array(env_list));
		perror("execve");
		exit(127);
	}

	// --- PAI ---
	close(fd);
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		*last_exit = 1;
		return (1);
	}
	if (WIFEXITED(status))
		*last_exit = WEXITSTATUS(status);
	else
		*last_exit = 1;
	return (*last_exit);
}
