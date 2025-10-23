/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:59:52 by matheusless       #+#    #+#             */
/*   Updated: 2025/10/23 11:59:53 by matheusless      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*envp_to_list(char **envp)
{
	t_env	*head = NULL;
	t_env	*tail = NULL;
	t_env	*new;
	int 	i;

	i = 0;
	while(envp[i])
	{
		char	*equal;
		char	*key;
		char	*value;

		equal = ft_strchr(envp[i], '=');
		if (!equal)
		{
			i++;
			continue;
		}
		key = ft_substr(envp[i], 0, equal - envp[i]);
		value = ft_strdup(equal + 1);
		if (!key || !value)
		{
			if (key)
				free(key);
			if (value)
				free(value);
			return (NULL);
		}
		new = create_env_node(key, value);
		if (!head)
		{
			head = new;
			tail = new;
		}
		else
		{
			tail->next = new;
			tail = new;
		}
		i++;
	}
	return (head);
}
