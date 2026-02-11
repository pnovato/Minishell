/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ast_aux_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:12:54 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 15:13:15 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*redirect_from_tokens(t_node *node, t_token *start, t_token *op)
{
	t_token	*op_prev;
	t_token	*op_next;

	op_prev = op_before(start, op);
	op_next = op->next;
	return (build_redirect_node(node, start, op_prev, op_next));
}

t_node	*pipe_from_tokens(t_node *node, t_token *start,
					t_token *end, t_token *op)
{
	t_pipe_args	a;

	a.start = start;
	a.op_prev = op_before(start, op);
	a.op_next = op->next;
	a.end = end;
	return (build_pipe_node(node, &a));
}
