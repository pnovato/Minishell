/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_the_inputs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:20:17 by matheusless       #+#    #+#             */
/*   Updated: 2025/09/26 14:09:23 by matheusless      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	execute_builtin(char **args, t_env *env)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, env));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args));
	else if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(env));
	else if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, env));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, env));
	return (1); 
}
