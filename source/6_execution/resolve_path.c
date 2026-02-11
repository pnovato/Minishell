/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:32:11 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 15:32:39 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**split_paths(t_env *env_list)
{
	char	*path_var;

	path_var = get_env_value("PATH", env_list);
	if (!path_var)
		return (NULL);
	return (ft_split(path_var, ':'));
}

char	*resolve_path(const char *cmd, t_env *env_list)
{
	char	**paths;
	char	*full;
	int		i;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = split_paths(env_list);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full = join_path(paths[i], cmd);
		if (full && access(full, X_OK) == 0)
			return (free_split(paths), full);
		free(full);
		i++;
	}
	free_split(paths);
	return (NULL);
}
