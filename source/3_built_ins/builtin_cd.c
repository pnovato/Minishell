/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:21:10 by matheusless       #+#    #+#             */
/*   Updated: 2025/10/10 16:12:19 by matheusless      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static char	*get_target_path(char **args)
{
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		return (getenv("OLDPWD"));
	if (args[1])
		return (args[1]);
	return (getenv("HOME"));
}

void	builtin_cd(char **args, t_env *env_list)
{
	char	cwd[1024];
	char	*path;

	(void)env_list;
	path = get_target_path(args);
	if (!path)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return ;
	}
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		ft_printf("%s\n", path);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd: getcwd");
		return ;
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return ;
	}
}
