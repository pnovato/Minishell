#include "../../include/minishell.h"

t_node *build_ast(t_token *start, t_token *end)
{
	t_token *op;
	char **args;

	op = find_last_operator(start, end);
	if (op)
		return (alloc_type(start, end, op));
	args = token_op_to_args(start, end);
	if (!args)
		return (NULL);
	return (new_cmd_node(args));
}

t_node *alloc_type(t_token *start, t_token *end, t_token *op)
{
	t_node *node;
	t_token *op_prev;
	t_token *op_next;
	t_node_type type;

	op_prev = op_before(start, op);
	op_next = op->next;
	if (!start || !end || !op || !op_next)
		return (NULL);
	type = check_token_type(op->value);
	node = new_op_node(type);
	if (!node)
		return (NULL);
	if (type == NODE_PIPE)
		return (build_pipe_node(node, start, op_prev, op_next, end));
	if (type == NODE_HEREDOC || is_redirect_type(type))
		return (build_redirect_node(node, start, op_prev, op_next));
	free(node);
	return (NULL);
}

t_token *ft_lstlast_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

t_token *find_last_operator(t_token *start, t_token *end)
{
	t_token *last_op;
	t_token *tmp;

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

t_token *op_before(t_token *start, t_token *target)
{
	t_token *tmp;
	t_token *before;

	tmp = start;
	before = NULL;
	while (tmp && tmp != target)
	{
		before = tmp;
		tmp = tmp->next;
	}
	return (before);
}