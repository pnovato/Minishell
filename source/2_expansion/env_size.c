/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:49:14 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 14:49:40 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	expand_loop(char *buffer, char **result, t_expand_ctx *ctx)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (buffer[i])
	{
		update_quotes(buffer[i], &sq, &dq);
		if (buffer[i] == '$' && !sq)
			handle_dollar(result, buffer, &i, ctx);
		else
			append_char_to_result(result, buffer[i]);
		i++;
	}
}
