#include "../../include/minishell.h"

int	exec_redirect(t_node *node, t_env *env_list, int *last_exit)
{
	int	fd;
	int	saved;
	
	if (!node->right || !node->right->redirect_file)
		return (1); //Saida generica, procurar saida correta
	printf("arquivo de redirecionamento: %s\n", node->redirect_file);
	if (node->type == NODE_RREDIRECT)
	{
		fd = open(node->redirect_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (perror("open"), 1); //saida generica, procurar saida correta
		saved = dup(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		*last_exit = exec_ast(node->left, env_list, last_exit);
		dup2(saved, STDOUT_FILENO);
		close(saved);
	}
	else if (node->type == NODE_LREDIRECT)
	{
		fd = open(node->redirect_file, O_RDONLY);
		if (fd < 0)
			return (perror("open"), 1);
		saved = dup(STDIN_FILENO);
		dup2(fd, STDIN_FILENO);
		close(fd);
		*last_exit = exec_ast(node->left, env_list, last_exit);
		dup2(saved, STDIN_FILENO);
		close(saved);
	}
	return (*last_exit);
}
