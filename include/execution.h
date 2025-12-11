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

typedef struct s_env t_env;
typedef struct s_node t_node;

# include "minishell.h"

char	*join_key_value(const char *key, const char *value);
char	*resolve_path(const char *cmd, t_env *env_list);
char	*join_path(const char *dir, const char *cmd);
char	**env_to_array(t_env *env);
int		is_builtin(const char *cmd);
int	exec_pipe_node(t_node *node, t_env *env_list, int *last_exit);
int	exec_ast(t_node *node, t_env *env_list, int *last_exit, int in_child);
int	exec_command_node(t_node *node, t_env *env_list, int *last_exit, int in_child);
int     exec_redirect(t_node *node, t_env *env_list, int *last_exit, int in_child);
int     exec_heredoc(t_node *node, t_env *env_list, int *last_exit);
t_node	*copy_ast(t_node *node);
void	resolve_heredocs(t_node *node, t_env *env_list, int *last_exit);
void	assert_tree_no_heredocs(t_node *node);
#endif
