/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:04:27 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 15:04:51 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	token_add_back(t_token **lst, t_token *nw)
{
	t_token	*node;

	if (!lst || !nw)
		return ;
	if (*lst == NULL)
	{
		*lst = nw;
		return ;
	}
	node = *lst;
	while (node->next != NULL)
		node = node->next;
	node->next = nw;
}

void	free_args_partial(char **args, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int	token_count(t_token *tok)
{
	int	count;

	count = 0;
	while (tok)
	{
		count++;
		tok = tok->next;
	}
	return (count);
}

t_lex	init_lex(int *i, int *s, t_token **l, t_quote *q)
{
	t_lex	lx;

	lx.i = i;
	lx.s = s;
	lx.l = l;
	lx.q = q;
	return (lx);
}

void	tokenize_step(char *line, t_lex *lx)
{
	check_quotes(line[*(lx->i)], &lx->q->is_single, &lx->q->is_double);
	if (!lx->q->is_single && !lx->q->is_double
		&& handle_double_redir(line, lx->i, lx->s, lx->l))
		return ;
	if (check_parenthesis_token(line, lx))
		return ;
	if (check_space_token(line, lx))
		return ;
	(*(lx->i))++;
}
