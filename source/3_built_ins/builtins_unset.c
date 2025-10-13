/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:24:21 by matheusless       #+#    #+#             */
/*   Updated: 2025/10/10 15:24:22 by matheusless      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	builtin_unset(char **args, t_env *env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env_var(&env, args[i]);
		i++;
	}
}
