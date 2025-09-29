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

# include "minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

void	handle_the_inputs(char *input, t_env *env_list);
void	builtin_echo(char **args);
void	builtin_pwd(void);
void	builtin_cd(char **args, t_env *env_list);
void	builtin_exit(char **args);

#endif
