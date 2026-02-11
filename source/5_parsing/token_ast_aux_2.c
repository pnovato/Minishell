/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ast_aux_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:06:10 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 15:12:41 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*new_cmd_node(char **args)
{
	t_node	*cmd;

	cmd = ft_calloc(1, sizeof(t_node));
	if (!cmd)
		return (NULL);
	cmd->type = NODE_COMMAND;
	cmd->av = args;
	cmd->redirect_file = NULL;
	cmd->redirect_type = 0;
	cmd->heredoc_fd = -1;
	cmd->left = NULL;
	cmd->right = NULL;
	return (cmd);
}

t_node	*new_op_node(t_type type)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->av = NULL;
	node->redirect_file = NULL;
	node->redirect_type = 0;
	node->heredoc_fd = -1;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_node	*build_redirect_node(t_node *node, t_token *start,
							t_token *op_prev, t_token *op_next)
{
	int	len;

	if (!op_next || !op_next->value)
		return (free_ast(node), NULL);
	if (node->type == NODE_HEREDOC)
	{
		len = ft_strlen(op_next->value);
		node->heredoc_expand = 1;
		if (len >= 2 && ((op_next->value[0] == '\''
					&& op_next->value[len - 1] == '\'') || (op_next->value[0]
					== '"' && op_next->value[len - 1] == '"')))
			node->heredoc_expand = 0;
		remove_one_token_quotes(op_next);
	}
	node->redirect_file = ft_strdup(op_next->value);
	if (!node->redirect_file)
		return (free_ast(node), NULL);
	node->left = build_ast(start, op_prev);
	if (!node->left)
		return (free_ast(node), NULL);
	return (node);
}

t_node	*build_pipe_node(t_node *node, t_pipe_args *a)
{
	node->left = build_ast(a->start, a->op_prev);
	node->right = build_ast(a->op_next, a->end);
	if (!node->left || !node->right)
		return (free_ast(node), NULL);
	return (node);
}

int	is_redirect_type(t_type type)
{
	if (type == NODE_RREDIRECT)
		return (1);
	if (type == NODE_LREDIRECT)
		return (1);
	if (type == NODE_APPEND)
		return (1);
	return (0);
}
