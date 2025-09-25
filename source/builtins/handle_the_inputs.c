/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_the_inputs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:20:17 by matheusless       #+#    #+#             */
/*   Updated: 2025/09/25 16:43:41 by matheusless      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	handle_the_inputs(char *input, t_env *env_list)
{
	char	**args;
	int		i;

	args = ft_split(input, ' ');
	if (!args || !args[0])
		return ;

	if (ft_strcmp(args[0], "echo") == 0)
		builtin_echo(args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(args[0], "cd") == 0)
		builtin_cd(args);
	else if (ft_strcmp(args[0], "exit") == 0)
		builtin_exit(args);
	else
		ft_printf("Comando não reconhecido: %s\n", args[0]);

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}
