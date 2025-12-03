/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:34:06 by matheusless       #+#    #+#             */
/*   Updated: 2025/12/03 00:20:32 by matheusless      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env t_env;

# include "minishell.h"

int		builtin_echo(char **args);
int     builtin_pwd(void);
int		builtin_cd(char **args, t_env *env);
int		builtin_exit(char **args);
int		builtin_env(t_env *env_list);
int		builtin_export(char **args, t_env *env);
int		builtin_unset(char **args, t_env *env);
void	update_env_value(t_env **env, const char *key, const char *value);
void	remove_env_var(t_env **env, const char *key);
int		execute_builtin(char **args, t_env *env_list);

#endif
