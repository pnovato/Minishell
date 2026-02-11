/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:50:39 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 14:50:46 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	append_char_to_result(char **result, char c)
{
	char	s[2];

	s[0] = c;
	s[1] = '\0';
	append_to_result(result, s);
}

void	expand_exit_status(char **result, int last_exit)
{
	char	*exit_str;

	exit_str = ft_itoa(last_exit);
	append_to_result(result, exit_str);
	free(exit_str);
}

void	expand_named_var(char **result, char *buf, int *i, t_env *env_list)
{
	int		j;
	char	*var_name;
	char	*value;

	j = *i + 1;
	while (ft_isalnum(buf[j]) || buf[j] == '_')
		j++;
	var_name = ft_substr(buf, *i + 1, j - (*i + 1));
	value = get_env_value(var_name, env_list);
	free(var_name);
	if (!value)
		value = "";
	append_to_result(result, value);
	*i = j - 1;
}

void	update_quotes(char c, int *sq, int *dq)
{
	if (c == '\'' && !(*dq))
		*sq = !(*sq);
	else if (c == '"' && !(*sq))
		*dq = !(*dq);
}

void	handle_dollar(char **result, char *buf, int *i, t_expand_ctx *ctx)
{
	if (buf[*i + 1] == '?')
	{
		expand_exit_status(result, ctx->last_exit);
		(*i)++;
	}
	else
		expand_named_var(result, buf, i, ctx->env_list);
}
