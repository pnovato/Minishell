#include "../../include/minishell.h"

int	exec_heredoc(t_node *node, t_env *env_list, int *last_exit)
{
	char	*line;
	int	pipe_fd[2];
	int	saved_stdin = dup(STDIN_FILENO);
	(void)env_list;
	(void)*last_exit;

	if (pipe(pipe_fd) == -1)
		return (1);
	//printf("[heredoc] heredoc_fd = %d (write-end)\n", pipe_fd[1]);
	while (1)
	{
		setup_signals_heredoc();
		line = readline("> ");
		if (g_signal_status == 130)
		{
			free(line);
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
			close(pipe_fd[1]);
			return (1);
		}
		if (!line || ft_strcmp(line, node->redirect_file) == 0)
		{
			free(line);
			break;
			//close(pipe_fd[1]);
			//dup2(saved_stdin, STDIN_FILENO);
			//close(saved_stdin);
			//return(1);
		}
		//printf("heredoc: linha = [%s]\n", line);
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		//setup_signals_main();
		free(line);
	}
	//printf("[heredoc] fechando pipe write-end (fd=%d)\n", pipe_fd[1]);
	close(pipe_fd[1]);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	node->heredoc_fd = pipe_fd[0];
	//printf("[heredoc] heredoc_fd final = %d (read-end)\n", node->heredoc_fd);
	node->type = NODE_LREDIRECT;
	//printf("heredoc: pipe criado com fd = %d\n", pipe_fd[0]);
	//if (g_signal_status == 130)
	//{
       		//int new_stdin = open("/dev/tty", O_RDONLY);
    		//if (new_stdin >= 0)
        	//	dup2(new_stdin, STDIN_FILENO);
		//return (1);
	//}	
	return (0);
}

int	resolve_heredocs(t_node *node, t_env *env_list, int *last_exit)
{
	t_node	*redirect;
	if (!node)
		return (0);

	if (node->type == NODE_HEREDOC)
	{
		if (exec_heredoc(node, env_list, last_exit) != 0)
		{
			//fprintf(stderr, "Erro ao processar heredoc.\n");
			*last_exit = 130;
			//fprintf(stderr, "Heredoc interrompido com Ctrl+C (status = %d)\n", *last_exit);
			return (1);
		}

		// Criar novo nó LREDIRECT para substituir o HEREDOC
		redirect = malloc(sizeof(t_node));
		if (!redirect)
		{
			//fprintf(stderr, "Heredoc interrompido com Ctrl+C (status = %d)\n", *last_exit);
			return (1);
		}

		memset(redirect, 0, sizeof(t_node));
		redirect->type = NODE_LREDIRECT;
		redirect->heredoc_fd = node->heredoc_fd;
		redirect->left = copy_ast(node->left);
		//redirect->right = NULL;
		//redirect->av = NULL;
		//redirect->redirect_file = NULL;

		// Substituir o conteúdo do node atual
		free_ast(node->left); // libertar a versão antiga
		*node = *redirect;
		free(redirect); // só o struct, os campos foram movidos
	}

	// Recursão para filhos
	if (resolve_heredocs(node->left, env_list, last_exit))
	{
		//fprintf(stderr, "Heredoc interrompido com Ctrl+C (status = %d)\n", *last_exit);
		return (1);
	}
	if (resolve_heredocs(node->right, env_list, last_exit))
	{
		//fprintf(stderr, "Heredoc interrompido com Ctrl+C (status = %d)\n", *last_exit);
		return (1);
	}
	return (0);
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
