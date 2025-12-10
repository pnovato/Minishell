#include "../../include/minishell.h"

int	exec_redirect(t_node *node, t_env *env_list, int *last_exit)
{
	int		fd;
	pid_t	pid;
	int		status;

	if (!node || !node->left)
		return (*last_exit = 1);
	// 1) Abrir o ficheiro de acordo com o tipo de redirecionamento
	if (node->heredoc_fd > 0)
	{
		//printf("HEREDOC DETECTADO: usando fd = %d\n", node->heredoc_fd);
		fd = node->heredoc_fd;
	}
	else if (node->type == NODE_RREDIRECT)          // comando > ficheiro
		fd = open(node->redirect_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->type == NODE_LREDIRECT)		// comando < ficheiro
	{
		if (!node->redirect_file)
			return (*last_exit = 1);
		fd = open(node->redirect_file, O_RDONLY);
	}
	else if (node->type == NODE_APPEND)
		fd = open(node->redirect_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (*last_exit = 1);	
	if (fd < 0)
		return (perror("open"), *last_exit = 1);
	// 2) Criar processo filho para executar o comando com FDs redirecionados
	pid = fork();
	if (pid == -1)
	{
		close (fd);
		return (perror("fork"), *last_exit = 1);
	}
	if (pid == 0)
	{
		// --- FILHO ---
		if (node->type == NODE_RREDIRECT || node->type == NODE_APPEND)
		{
			//printf("Redirecionando STDOUT com fd = %d\n", fd);
			dup2(fd, STDOUT_FILENO);
		}
		else
		{
			//printf("Redirecionando STDIN com fd = %d\n", fd);
			dup2(fd, STDIN_FILENO);
		}
		close (fd);
		exit (exec_ast(node->left, env_list, last_exit));
	}

	// --- PAI ---
	close(fd);
	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid"), *last_exit = 1);
	if (WIFEXITED(status))
		*last_exit = WEXITSTATUS(status);
	else
		*last_exit = 1;
	return (*last_exit);
}
