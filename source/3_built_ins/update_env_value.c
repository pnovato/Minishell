/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:25:07 by matheusless       #+#    #+#             */
/*   Updated: 2025/10/10 16:14:03 by matheusless      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static void	append_new_env(t_env **env, const char *key, const char *value)
{
	t_env	*curr;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!*env)
	{
		*env = new;
		return ;
	}
	curr = *env;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

void	update_env_value(t_env **env, const char *key, const char *value)
{
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			curr->value = ft_strdup(value);
			return ;
		}
		curr = curr->next;
	}
	append_new_env(env, key, value);
}
