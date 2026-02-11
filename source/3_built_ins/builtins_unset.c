/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:59:06 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 15:01:13 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	is_valid_unset_key(char *key)
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

int	builtin_unset(char **args, t_env *env)
{
	int	i;
	int	exit_code;

	i = 1;
	exit_code = 0;
	while (args[i])
	{
		if (is_valid_unset_key(args[i]))
			remove_env_var(&env, args[i]);
		else
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_code = 1;
		}
		i++;
	}
	return (exit_code);
}
