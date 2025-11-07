#include "../../include/minishell.h"

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
