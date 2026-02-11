/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:50:57 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 14:53:25 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_value(const char *key, t_env *env_list)
{
	while (env_list)
	{
		if (ft_strcmp(key, env_list->key) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

void	append_to_result(char **result, const char *add)
{
	char	*tmp;

	tmp = ft_strjoin(*result, add);
	free(*result);
	*result = tmp;
}

char	*expand_env_variables(char *input, t_env *env_list, int last_exit)
{
	char			*buffer;
	char			*result;
	t_expand_ctx	ctx;

	buffer = ft_strdup(input);
	result = ft_strdup("");
	ctx.env_list = env_list;
	ctx.last_exit = last_exit;
	expand_loop(buffer, &result, &ctx);
	free(buffer);
	return (result);
}

void	expand_token_list(t_token *token_list, t_env *env_list, int last_exit)
{
	char	*expanded;

	while (token_list)
	{
		if (token_list->type == NODE_COMMAND
			|| token_list->type == NODE_FILENAME)
		{
			expanded = expand_env_variables(token_list->raw_value,
					env_list, last_exit);
			free(token_list->value);
			token_list->value = expanded;
		}
		token_list = token_list->next;
	}
}

void	remove_token_quotes(t_token *token)
{
	int		len;
	char	*stripped;

	while (token)
	{
		len = ft_strlen(token->value);
		if (len >= 2
			&& ((token->value[0] == '\'' && token->value[len - 1] == '\'')
				|| (token->value[0] == '"' && token->value[len - 1] == '"')))
		{
			stripped = ft_substr(token->value, 1, len - 2);
			free(token->value);
			token->value = stripped;
		}
		token = token->next;
	}
}
