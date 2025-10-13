/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:26:38 by matheusless       #+#    #+#             */
/*   Updated: 2025/10/10 15:26:39 by matheusless      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*create_env_node(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		free(new);
		return (NULL);
	}
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}
