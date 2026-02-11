/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:47:57 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 14:48:58 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_kv(char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
}

static int	extract_kv(char *env, char **key, char **value)
{
	char	*equal;

	*key = NULL;
	*value = NULL;
	equal = ft_strchr(env, '=');
	if (!equal)
		return (0);
	*key = ft_substr(env, 0, equal - env);
	*value = ft_strdup(equal + 1);
	if (!*key || !*value)
	{
		free_kv(*key, *value);
		return (-1);
	}
	return (1);
}

static int	append_env_node(t_env **head, t_env **tail, char *key, char *value)
{
	t_env	*new;

	new = create_env_node(key, value);
	if (!new)
	{
		free_kv(key, value);
		return (0);
	}
	if (!*head)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		(*tail)->next = new;
		*tail = new;
	}
	return (1);
}

static int	fill_env_list(t_env **head, t_env **tail, char **envp)
{
	int		i;
	int		ret;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		ret = extract_kv(envp[i], &key, &value);
		if (ret == -1)
			return (0);
		if (ret == 1 && !append_env_node(head, tail, key, value))
			return (0);
		i++;
	}
	return (1);
}

t_env	*envp_to_list(char **envp)
{
	t_env	*head;
	t_env	*tail;

	head = NULL;
	tail = NULL;
	if (!fill_env_list(&head, &tail, envp))
		return (free_env_list(head), NULL);
	return (head);
}
