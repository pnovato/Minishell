/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:23:31 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 15:23:31 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**env_to_array(t_env *env)
{
	int		count;
	char	**envp;
	int		i;

	count = env_size(env);
	envp = malloc(sizeof(char *) * (count + 1));
	i = 0;
	if (!envp)
		return (NULL);
	while (env)
	{
		envp[i++] = join_key_value(env->key, env->value);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
