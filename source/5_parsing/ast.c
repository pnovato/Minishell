/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:05:18 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 15:05:57 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*build_ast(t_token *start, t_token *end)
{
	t_token	*op;
	char	**args;

	op = find_last_operator(start, end);
	if (op)
		return (alloc_type(start, end, op));
	args = token_op_to_args(start, end);
	if (!args)
		return (NULL);
	return (new_cmd_node(args));
}

t_node	*alloc_type(t_token *start, t_token *end, t_token *op)
{
	t_node	*node;

	if (!start || !end || !op || !op->next)
		return (NULL);
	node = new_op_node(check_token_type(op->value));
	if (!node)
		return (NULL);
	if (node->type == NODE_PIPE)
		return (pipe_from_tokens(node, start, end, op));
	if (node->type == NODE_HEREDOC || is_redirect_type(node->type))
		return (redirect_from_tokens(node, start, op));
	free(node);
	return (NULL);
}

t_token	*ft_lstlast_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

t_token	*find_last_operator(t_token *start, t_token *end)
{
	t_token	*last_op;
	t_token	*tmp;

	last_op = NULL;
	tmp = start;
	while (tmp && tmp != end->next)
	{
		if (check_token_type(tmp->value) != NODE_COMMAND)
			last_op = tmp;
		tmp = tmp->next;
	}
	return (last_op);
}

t_token	*op_before(t_token *start, t_token *target)
{
	t_token	*tmp;
	t_token	*before;

	tmp = start;
	before = NULL;
	while (tmp && tmp != target)
	{
		before = tmp;
		tmp = tmp->next;
	}
	return (before);
}
