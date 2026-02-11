/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:02:49 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 15:03:47 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_double_redir(char *line, int *i, int *start, t_token **tok)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		init_token_slice(tok, line, *start, *i);
		init_token_slice(tok, line, *i, *i + 2);
		*i += 2;
		*start = *i;
		return (1);
	}
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		init_token_slice(tok, line, *start, *i);
		init_token_slice(tok, line, *i, *i + 2);
		*i += 2;
		*start = *i;
		return (1);
	}
	return (0);
}

t_token	*new_token(char *value, t_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->raw_value = ft_strdup(value);
	token->value = ft_strdup(value);
	if (!token->raw_value || !token->value)
	{
		free(token->raw_value);
		free(token->value);
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

void	init_token_slice(t_token **lst, char *line, int start, int end)
{
	char	*value;
	t_type	type;
	t_token	*new;

	if (end <= start)
		return ;
	value = ft_substr(line, start, end - start);
	if (!value)
		return ;
	type = check_token_type(value);
	new = new_token(value, type);
	free(value);
	if (new)
		token_add_back(lst, new);
}

t_token	*split_line_to_token(char *line)
{
	int		i;
	int		start;
	t_token	*token;
	t_quote	q;
	t_lex	lx;

	i = 0;
	start = 0;
	token = NULL;
	q.is_single = false;
	q.is_double = false;
	lx = init_lex(&i, &start, &token, &q);
	while (line[i])
		tokenize_step(line, &lx);
	init_token_slice(&token, line, start, i);
	return (token);
}

char	**token_list_to_args(t_token *token)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (token_count(token) + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (token)
	{
		args[i] = ft_strdup(token->value);
		if (!args[i])
			return (free_args_partial(args, i), NULL);
		i++;
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}
