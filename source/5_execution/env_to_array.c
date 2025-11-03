/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:32:19 by matheusless       #+#    #+#             */
/*   Updated: 2025/10/23 14:46:35 by matheusless      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**env_to_array(t_env *env)
{
	int		count = env_size(env);
	char	**envp = malloc(sizeof(char *) * (count + 1));
	int		i = 0;

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
