#include "../../include/minishell.h"

char **token_op_to_args(t_token *start, t_token *end)
{
	int	count;
	t_token	*tmp;
	char	**args;
	int	i;

	count = 0;
	tmp = start;
	i = 0;
	if (!tmp->value)
	{
    		//printf("token_range_to_args: NULL token value detectado!\n");
    		return NULL;
	}
	while (tmp && tmp != end->next)
	{
		if (check_token_type(tmp->value) != NODE_COMMAND)
		{
			//printf("token_range_to_args: operador encontrado = %s\n", tmp->value);
			return (NULL);
		}
		count++;
		tmp = tmp->next;
	}
	args = malloc(sizeof(char *) * (count + 1));
	tmp = start;
	while(i < count)
	{
		args[i] = ft_strdup(tmp->value);
		if (!args[i])
		{
   			 //printf("Falha ao duplicar token: %s\n", tmp->value);
    			free_split(args);
    			return NULL;
		}
		tmp = tmp->next;
		i++;
	}
	args[count] = NULL;
	return (args);
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
