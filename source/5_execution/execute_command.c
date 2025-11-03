/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:28:11 by matheusless       #+#    #+#             */
/*   Updated: 2025/10/23 15:14:07 by matheusless      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_command(char **args, t_env *env_list, int *last_exit)
{
	pid_t pid;
	int status;
	char *cmd_path = resolve_path(args[0], env_list);
	char **envp = env_to_array(env_list);

	if (!cmd_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(args[0], 2);
		*last_exit = 127;
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, args, envp);
		perror("execve");
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
		*last_exit = WEXITSTATUS(status);
	}
	free(cmd_path);
	free_split(envp);
}
