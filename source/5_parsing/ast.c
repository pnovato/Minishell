#include "../../include/minishell.h"

t_node  *build_ast(t_token *start, t_token *end)
{
       t_token	*op;
       t_node	*cmd;

       op = find_last_operator(start, end);

       if (op)
	       return (alloc_type(start, end, op));
       cmd = malloc(sizeof(t_node));
       if (!cmd)
	       return NULL;
       printf("build_ast: intervalo [%s] ... [%s]\n", start->value, end->value);
       cmd->type = NODE_COMMAND;
       cmd->av = token_op_to_args(start, end);
       cmd->redirect_file = NULL;
       cmd->redirect_type = 0;
       cmd->left = NULL;
       cmd->right = NULL;
       char **args = token_op_to_args(start, end);
       if (!args)
       {
	       free(cmd);
	       return NULL;
       }
       cmd->av = args;
       return (cmd);
}


t_node  *alloc_type(t_token *start, t_token *end, t_token *op)
{       
        t_node	*node;
	
	if (!start || !end || !op || !op->next)
		return (NULL);
	if (start == op || end == op)
		return (NULL);
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	printf("alloc_type: operador = %s\n", op->value);
	node->type = check_token_type(op->value);
	node->av = NULL;
	node->redirect_file = NULL;
	node->redirect_type = 0;
	node->left = build_ast(start, op_before(start, op));
	node->right = build_ast(op->next, end);
	if (!node->left || !node->right)
	{
		free(node);
		return (NULL);
	}
	return (node);
}
