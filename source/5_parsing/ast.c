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


t_node  *alloc_type(t_token **start, t_token **end, t_node_type str)
{       
        
}  
