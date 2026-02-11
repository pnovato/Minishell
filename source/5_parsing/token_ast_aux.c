/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ast_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:13:23 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 15:15:18 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_cmd_token(t_token *tok)
{
	if (!tok->value || tok->value[0] == '\0')
		return (0);
	if (check_token_type(tok->value) != NODE_COMMAND)
		return (0);
	return (1);
}

int	count_cmd_tokens(t_token *start, t_token *end)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = start;
	while (tmp && tmp != end->next)
	{
		if (is_cmd_token(tmp))
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	fill_args(char **args, t_token *start, t_token *end)
{
	t_token	*tmp;
	int		i;

	tmp = start;
	i = 0;
	while (tmp && tmp != end->next)
	{
		if (is_cmd_token(tmp))
		{
			args[i] = ft_strdup(tmp->value);
			if (!args[i])
				return (free_args_partial(args, i), 0);
			i++;
		}
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (1);
}

char	**token_op_to_args(t_token *start, t_token *end)
{
	char	**args;
	int		count;

	count = count_cmd_tokens(start, end);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	if (!fill_args(args, start, end))
		return (NULL);
	return (args);
}

void	remove_one_token_quotes(t_token *token)
{
	int		len;
	char	*stripped;

	if (!token || !token->value)
		return ;
	len = ft_strlen(token->value);
	if (len >= 2 && ((token->value[0] == '\'' && token->value[len - 1]
				== '\'') || (token->value[0]
				== '"' && token->value[len - 1] == '"')))
	{
		stripped = ft_substr(token->value, 1, len - 2);
		free(token->value);
		token->value = stripped;
	}
}
