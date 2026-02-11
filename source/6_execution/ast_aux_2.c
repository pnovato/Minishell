/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_aux_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:18:10 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 15:20:33 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_ast_heredoc_node(t_node *node, t_shell *sh,
	int *last_exit, int in_child)
{
	t_node	*old_left;

	heredoc_forbidden_in_child(in_child);
	if (exec_heredoc(node, sh, last_exit) != 0)
		return (1);
	old_left = node->left;
	if (node->left && node->left->type == NODE_HEREDOC)
		node->left->type = NODE_LREDIRECT;
	node->type = NODE_LREDIRECT;
	node->left = copy_ast(old_left);
	clear_node_fields(node);
	if (!node->left)
		return (free_ast(old_left), 1);
	return (exec_after_heredoc(node, sh, last_exit, old_left));
}

void	print_cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	apply_heredoc_fd(t_node *node)
{
	if (node->heredoc_fd > 0)
		dup2(node->heredoc_fd, STDIN_FILENO);
	if (node->heredoc_fd > 2)
		close(node->heredoc_fd);
}

void	execve_or_die(t_node *node, t_shell *sh, char *path)
{
	char	**envp;

	setup_signals_child();
	apply_heredoc_fd(node);
	close_fds_from(3);
	envp = env_to_array(sh->env);
	execve(path, node->av, envp);
	perror("execve");
	free_envp(envp);
	free(path);
	_exit(127);
}
