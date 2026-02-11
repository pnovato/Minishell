/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:57:23 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 17:03:27 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	is_valid_export_key(char *key)
{
	int	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_process_arg(char *arg, t_env **env)
{
	char	*eq;
	char	*key;

	eq = ft_strchr(arg, '=');
	if (eq)
		key = ft_substr(arg, 0, eq - arg);
	else
		key = ft_strdup(arg);
	if (!is_valid_export_key(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(key);
		return (1);
	}
	if (eq)
		update_env_value(env, key, eq + 1);
	else
		ensure_env_key(env, key);
	free(key);
	return (0);
}

int	builtin_export(char **args, t_env *env)
{
	int	i;
	int	exit_code;

	i = 1;
	exit_code = 0;
	if (!args[1])
		return (export_print(env));
	while (args[i])
	{
		if (export_process_arg(args[i], &env))
			exit_code = 1;
		i++;
	}
	return (exit_code);
}

int	export_print(t_env *env)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (cur->key)
			ft_putstr_fd(cur->key, STDOUT_FILENO);
		if (cur->value && cur->value[0] != '\0')
		{
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(cur->value, STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		cur = cur->next;
	}
	return (0);
}
