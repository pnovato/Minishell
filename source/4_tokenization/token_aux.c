#include "../../include/minishell.h"

void token_add_back(t_token **lst, t_token *nw)
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

void free_args_partial(char **args, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int token_count(t_token *tok)
{
	int count;

	count = 0;
	while (tok)
	{
		count++;
		tok = tok->next;
	}
	return (count);
}
