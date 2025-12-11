#include "../../include/minishell.h"

int	exec_heredoc(t_node *node, t_env *env_list, int *last_exit)
{
	char	*line;
	int	pipe_fd[2];
	(void)env_list;
	(void)*last_exit;

	if (pipe(pipe_fd) == -1)
		return (1);
	//printf("[heredoc] heredoc_fd = %d (write-end)\n", pipe_fd[1]);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, node->redirect_file) == 0)
		{
			free(line);
			break;
		}
		//printf("heredoc: linha = [%s]\n", line);
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	//printf("[heredoc] fechando pipe write-end (fd=%d)\n", pipe_fd[1]);
	close(pipe_fd[1]);
	node->heredoc_fd = pipe_fd[0];
	//printf("[heredoc] heredoc_fd final = %d (read-end)\n", node->heredoc_fd);
	node->type = NODE_LREDIRECT;
	//printf("heredoc: pipe criado com fd = %d\n", pipe_fd[0]);
	return (0);
}

void	resolve_heredocs(t_node *node, t_env *env_list, int *last_exit)
{
	if (!node)
		return;

	if (node->type == NODE_HEREDOC)
	{
		if (exec_heredoc(node, env_list, last_exit) != 0)
		{
			fprintf(stderr, "Erro ao processar heredoc.\n");
			return;
		}

		// Criar novo nó LREDIRECT para substituir o HEREDOC
		t_node *redirect = malloc(sizeof(t_node));
		if (!redirect)
			return;

		memset(redirect, 0, sizeof(t_node));
		redirect->type = NODE_LREDIRECT;
		redirect->heredoc_fd = node->heredoc_fd;
		redirect->left = copy_ast(node->left);
		redirect->right = NULL;
		redirect->av = NULL;
		redirect->redirect_file = NULL;

		// Substituir o conteúdo do node atual
		free_ast(node->left); // libertar a versão antiga
		*node = *redirect;
		free(redirect); // só o struct, os campos foram movidos
	}

	// Recursão para filhos
	resolve_heredocs(node->left, env_list, last_exit);
	resolve_heredocs(node->right, env_list, last_exit);
}


void	assert_tree_no_heredocs(t_node *node)
{
	if (!node)
		return;

	if (node->type == NODE_HEREDOC)
	{
		fprintf(stderr, "Erro: HEREDOC ainda presente na AST! Deve ser resolvido antes da execução.\n");
		exit(1);
	}

	assert_tree_no_heredocs(node->left);
	assert_tree_no_heredocs(node->right);
}
