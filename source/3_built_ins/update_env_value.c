/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:00:42 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 15:01:00 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	set_env_value(t_env *node, const char *value)
{
	char	*dup;

	dup = ft_strdup(value);
	if (!dup)
		return (0);
	free(node->value);
	node->value = dup;
	return (1);
}

static t_env	*new_env_node(const char *key, const char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!new->key)
		return (free(new), NULL);
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new->key);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

static void	append_env_node(t_env **env, t_env *new)
{
	t_env	*cur;

	if (!*env)
	{
		*env = new;
		return ;
	}
	cur = *env;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

void	update_env_value(t_env **env, const char *key, const char *value)
{
	t_env	*cur;
	t_env	*new;

	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			set_env_value(cur, value);
			return ;
		}
		cur = cur->next;
	}
	new = new_env_node(key, value);
	if (!new)
		return ;
	append_env_node(env, new);
}
