#include "../../include/minishell.h"

t_node  *build_ast(t_token *start, t_token *end)
{
        t_token *tmp;
        t_node  *node;

        tmp = end;
        while (temp && temp != start)
        {
                if (tmp->type == check_token_type(tmp->type))
                        node = alloc_type(&start, end, tmp->type);
                tmp = tmp->
        }
}


t_node  *alloc_type(t_token *start, t_token *end, t_token *op)
{       
        t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = check_token_type(op->value);
	node->av = NULL;
	node->redirect_file = NULL;
	node->redirect_type = 0;
	node->left = build_ast(start, op_before(start, op));
	node->right = build_ast(op->next, end);
	return (node);
}
