/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:26:46 by matheusless       #+#    #+#             */
/*   Updated: 2025/10/10 15:26:47 by matheusless      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = temp;
	}
}
