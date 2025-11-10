/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_the_inputs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:20:17 by matheusless       #+#    #+#             */
/*   Updated: 2025/09/26 14:09:23 by matheusless      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	execute_builtin(char **args, t_env *env_list)
{
	if (ft_strcmp(args[0], "echo") == 0)
		builtin_echo(args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(args[0], "cd") == 0)
		builtin_cd(args, env_list);
	else if (ft_strcmp(args[0], "exit") == 0)
		builtin_exit(args);
	else if (ft_strcmp(args[0], "env") == 0)
		builtin_env(env_list);
	else if (ft_strcmp(args[0], "export") == 0)
		builtin_export(args, env_list);
	else if (ft_strcmp(args[0], "unset") == 0)
		builtin_unset(args, env_list);
	else
		ft_printf("Comando não reconhecido: %s\n", args[0]);
}


void	handle_the_inputs(char **args, t_env *env_list, int *last_exit)
{
	if (!args || !args[0])
		return ;
	if (is_builtin(args[0]))
		execute_builtin(args, env_list);
	else
		execute_command(args, env_list, last_exit);
}
