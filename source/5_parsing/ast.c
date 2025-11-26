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
       //printf("build_ast: intervalo [%s] ... [%s]\n", start->value, end->value);
       cmd->type = NODE_COMMAND;
       cmd->av = token_op_to_args(start, end);
       cmd->redirect_file = NULL;
       cmd->redirect_type = 0;
	cmd->heredoc_fd = 0;
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
	t_token	*op_prev;
	t_token	*op_next;
	
	op_prev = op_before(start, op);
	op_next = op->next;

	if (!start || !end || !op || !op_next)
		return (NULL);
	
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = check_token_type(op->value);
	node->av = NULL;
	node->redirect_file = NULL;
	node->left = NULL;
	node->right = NULL;

        if (node->type == NODE_HEREDOC)
        {
                node->left = build_ast(start, op_prev);
                node->redirect_file = ft_strdup(op_next->value);
                node->right = NULL;
                if (!node->left || !node->redirect_file)
                {
                        free(node->redirect_file);
                        free(node);
                        return (NULL);
                }
                return (node);
        }


	if (node->type == NODE_PIPE)
	{
		node->left = build_ast(start, op_prev);
		node->right = build_ast(op_next, end);
		
		if (!node->left || !node->right)
		{
			free(node);
			return (NULL);
		}
		return (node);
	}

	if (node->type == NODE_RREDIRECT || node->type == NODE_LREDIRECT)
	{
		node->left = build_ast(start, op_prev);
		node->redirect_file = ft_strdup(op_next->value);
		node->right = NULL;
		if (!node->left || !node->redirect_file)
		{
			free(node->redirect_file);
			free(node);
			return (NULL);
		}
		return (node);
	}
	free(node);
	return (NULL);
}
