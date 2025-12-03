/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:44:00 by ...               #+#    #+#             */
/*   Updated: 2025/12/02 23:18:46 by matheusless      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_pipe_node(t_node *node, t_env *env_list, int *last_exit)
{
	int		pipefd[2];
	int		status;	
	pid_t	left;
	pid_t	right;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	left = fork();
	if (left == -1)
		return (perror("fork"), 1);
	if (left == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exit(exec_ast(node->left, env_list, last_exit));
	}
	right = fork();
	if (right == -1)
		return (perror("fork"), 1);
	if (right == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exit(exec_ast(node->right, env_list, last_exit));
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(left, &status, 0);
	waitpid(right, &status, 0);
	if (WIFEXITED(status))
		*last_exit = WEXITSTATUS(status); // CORREÇÃO: Usando WEXITSTATUS
	else if (WIFSIGNALED(status))
		*last_exit = 128 + WTERMSIG(status); // Tratamento de sinais (opcional, mas recomendado)
	return (*last_exit);
}
