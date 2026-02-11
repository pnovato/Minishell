/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_aux_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:16:56 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 15:45:02 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_unsupported_in_child(int in_child, int *last_exit)
{
	if (in_child)
		_exit(*last_exit);
	return (*last_exit);
}

int	is_empty_cmd(t_node *node)
{
	if (node->type != NODE_COMMAND)
		return (0);
	if (!node->av || !node->av[0])
		return (1);
	return (0);
}

void	heredoc_forbidden_in_child(int in_child)
{
	if (!in_child)
		return ;
	_exit(1);
}

void	clear_node_fields(t_node *node)
{
	free(node->right);
	free(node->redirect_file);
	free(node->av);
	node->right = NULL;
	node->redirect_file = NULL;
	node->av = NULL;
}

int	exec_after_heredoc(t_node *node, t_shell *sh,
	int *last_exit, t_node *old_left)
{
	int	result;

	result = exec_ast(node, sh, last_exit, 0);
	free_ast(old_left);
	return (result);
}
