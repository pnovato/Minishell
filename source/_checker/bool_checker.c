/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:45:43 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 14:46:59 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_quotes(char str, bool *is_single, bool *is_double)
{
	if (str == '\'' && !(*is_double))
		*is_single = !(*is_single);
	else if (str == '"' && !(*is_single))
		*is_double = !(*is_double);
}

bool	check_parenthesis_token(char *lin, t_lex *lx)
{
	if (!(lx->q->is_single) && !(lx->q->is_double)
		&& (lin[*(lx->i)] == '(' || lin[*(lx->i)] == ')'))
	{
		if (*(lx->i) > *(lx->s))
			init_token_slice(lx->l, lin, *(lx->s), *(lx->i));
		init_token_slice(lx->l, lin, *(lx->i), *(lx->i) + 1);
		(*(lx->i))++;
		while (lin[*(lx->i)] == ' ')
			(*(lx->i))++;
		*(lx->s) = *(lx->i);
		return (true);
	}
	return (false);
}

bool	check_space_token(char *lin, t_lex *lx)
{
	if (!(lx->q->is_single) && !(lx->q->is_double) && lin[*(lx->i)] == ' ')
	{
		if (*(lx->i) > *(lx->s))
			init_token_slice(lx->l, lin, *(lx->s), *(lx->i));
		while (lin[*(lx->i)] == ' ')
			(*(lx->i))++;
		*(lx->s) = *(lx->i);
		return (true);
	}
	return (false);
}

bool	is_operator(char *str, int i)
{
	if (str[i] == '|')
		return (true);
	else if (str[i] == '>')
		return (true);
	else if (str[i] == '<')
		return (true);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (true);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (true);
	else if (str[i] == '&' && str[i + 1] == '&')
		return (true);
	else if (str[i] == '|' && str[i + 1] == '|')
		return (true);
	return (false);
}

bool	has_operator(t_token *token)
{
	while (token)
	{
		if (check_token_type(token->value) != NODE_COMMAND)
			return (true);
		token = token->next;
	}
	return (false);
}
