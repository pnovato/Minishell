#include "../../include/minishell.h"

t_token	*new_token(char *value, t_node_type *type)
{
	t_token *token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value); //aloquei memoria, depois preciso dar free nela. talvez um free_token_list;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	token_add_back(t_token **lst, t_token **new)
{
	t_token *node;

	if (!lst || !new)
		return;
	if (*lst = NULL)
	{
		lst = new;
		return;
	}
	node = new;
	while (node->next != NULL)
		node = node->next;
	node->next = new;
}

t_token	*split_line_to_token(char *line)
{
	int	i;
	int	start;
	t_token	*token;
	
	i = 0;
	start = 0;
	token = NULL;
	while (line[i])
	{
		while (line[i] && line[i] = ' ')
			i++;
		if (i > start)
			new_token()
	}
}
