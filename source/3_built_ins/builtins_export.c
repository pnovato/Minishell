/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:44:00 by ...               #+#    #+#             */
/*   Updated: 2025/12/03 00:26:09 by matheusless      ###   ########.fr       */
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

int	builtin_export(char **args, t_env *env)
{
	int		i;
	int		exit_code;
	char	*eq;
	char	*key;

	i = 1;
	exit_code = 0;
	if (!args[1])
	{
		return (0);
	}
	while (args[i])
	{
		eq = ft_strchr(args[i], '=');
		if (eq)
			key = ft_substr(args[i], 0, eq - args[i]);
		else
			key = ft_strdup(args[i]);
		if (!is_valid_export_key(key))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_code = 1;
		}
		else if (eq)
		{
			update_env_value(&env, key, eq + 1);
		}
		free(key);
		i++;
	}
	return (exit_code);
}
