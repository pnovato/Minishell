/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:34:06 by matheusless       #+#    #+#             */
/*   Updated: 2025/09/26 14:10:13 by matheusless      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env t_env;

# include "minishell.h"

void	handle_the_inputs(char **args, t_env *env_list, int *last_exit);
void	builtin_echo(char **args);
void	builtin_pwd(void);
void	builtin_cd(char **args, t_env *env_list);
void	builtin_exit(char **args);
void	builtin_env(t_env *env);
void	builtin_export(char **args, t_env *env);
void	builtin_unset(char **args, t_env *env);
void	update_env_value(t_env **env, const char *key, const char *value);
void	remove_env_var(t_env **env, const char *key);

#endif
