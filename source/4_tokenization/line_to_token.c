#include "../../include/minishell.h"

t_token	*new_token(char *value, t_node_type type)
{
	t_token *token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value); //aloquei memoria, depois preciso dar free nela. talvez um free_token_list;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	token_add_back(t_token **lst, t_token *nw)
{
	t_token *node;

	if (!lst || !nw)
		return;
	if (*lst == NULL)
	{
		*lst = nw;
		return;
	}
	node = *lst;
	while (node->next != NULL)
		node = node->next;
	node->next = nw;
}

void	init_token_slice(t_token **lst, char *line, int start, int end)
{
	char		*value;
	t_node_type	type;
	t_token		*new;
	
	value = ft_substr(line, start, end - start);
	type = check_token_type(value);
	new = new_token(value, type);
	free(value);
	if (new)
		token_add_back(lst, new);
}


t_token	*split_line_to_token(char *line)
{
	int	i;
	int	start;
	t_token	*token;
	t_quote	q;

	i = 0;
	start = 0;
	token = NULL;
	q.is_single = false;
	q.is_double = false;
	while (line[i])
	{
		check_quotes(line[i], &q.is_single, &q.is_double);
		if (check_parenthesis_token(line, &i, &start, &token, &q))
			continue;
		if (check_space_token(line, &i, &start, &token, &q))
			continue;
		i++;
	}
	if (i > start)
		init_token_slice(&token, line, start, i);
	return (token);
}
