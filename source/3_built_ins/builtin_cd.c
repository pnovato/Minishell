/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:44:00 by ...               #+#    #+#             */
/*   Updated: 2025/12/03 01:54:38 by matheusless      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static char	*get_cd_path(char **args)
{
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		return (getenv("OLDPWD"));
	if (args[1])
		return (args[1]);
	return (getenv("HOME"));
}

int	builtin_cd(char **args, t_env *env_list)
{
	char	cwd[1024];
	char	*path;

	(void)env_list;
	path = get_cd_path(args);
	if (!path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		ft_printf("%s\n", path);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
