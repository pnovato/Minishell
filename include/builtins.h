/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:04:02 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 16:39:10 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct s_env	t_env;
typedef struct s_shell	t_shell;

int		builtin_echo(char **args);
int		builtin_pwd(void);
int		builtin_cd(char **args, t_env *env_list);
int		builtin_exit(t_shell *sh, char **args);
int		builtin_env(t_env *env);
int		builtin_export(char **args, t_env *env);
int		builtin_unset(char **args, t_env *env);
void	update_env_value(t_env **env, const char *key, const char *value);
void	remove_env_var(t_env **env, const char *key);
int		execute_builtin(char **args, t_env *env_list, t_shell *sh);
int		export_print(t_env *env);
t_env	*find_env_node(t_env *env, char *key);
void	ensure_env_key(t_env **env, char *key);

#endif
