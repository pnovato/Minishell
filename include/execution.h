/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:27:53 by matheusless       #+#    #+#             */
/*   Updated: 2025/10/23 14:39:54 by matheusless      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "builtins.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

void	execute_command(char **args, t_env *env_list, int *last_exit);
char	*join_key_value(const char *key, const char *value);
char	*resolve_path(const char *cmd, t_env *env_list);
char	*join_path(const char *dir, const char *cmd);
char	**env_to_array(t_env *env);
int		is_builtin(const char *cmd);

#endif
