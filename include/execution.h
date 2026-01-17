#ifndef EXECUTION_H
#define EXECUTION_H

typedef struct s_env t_env;
typedef struct s_node t_node;
typedef struct s_shell t_shell;
typedef struct s_token t_token;

#include "minishell.h"

char *join_key_value(const char *key, const char *value);
char *resolve_path(const char *cmd, t_env *env_list);
char *join_path(const char *dir, const char *cmd);
char **env_to_array(t_env *env);
int is_builtin(const char *cmd);
int exec_pipe_node(t_node *node, t_shell *sh, int *last_exit);
int exec_ast(t_node *node, t_shell *sh, int *last_exit, int in_child);
int exec_command_node(t_node *node, t_shell *sh, int *last_exit, int in_child);
int exec_redirect(t_node *node, t_shell *sh, int *last_exit, int in_child);
int exec_heredoc(t_node *node, t_shell *sh, int *last_exit);
t_node *copy_ast(t_node *node);
int resolve_heredocs(t_node *node, t_shell *sh, int *last_exit);
void assert_tree_no_heredocs(t_node *node);
void cleanup_child(t_shell *sh);
void cleanup_child_min(t_node *ast, t_token *tokens, t_env *env, char *line);
void close_fds_from(int start);

int transform_heredoc_node(t_node *node);
int heredoc_wait_parent(pid_t pid, int rfd, int *last_exit);
void run_heredoc_child(t_node *node, t_shell *sh, int *pipe_fd, int last_exit);
int heredoc_child_loop(t_node *node, t_shell *sh, int wfd, int last_exit);
void close_if_valid(int *fd);

int open_redirect_fd(t_node *node);
int is_input_redirect(t_node *node);
void save_std_fds(t_node *node, int *saved_in, int *saved_out);
void restore_std_fds(int saved_in, int saved_out);
void apply_redirect(t_node *node, int fd);

int exec_unsupported_in_child(int in_child, int *last_exit);
int is_empty_cmd(t_node *node);
void heredoc_forbidden_in_child(int in_child);
void clear_node_fields(t_node *node);
int exec_after_heredoc(t_node *node, t_shell *sh,
                       int *last_exit, t_node *old_left);

int exec_ast_heredoc_node(t_node *node, t_shell *sh,
                          int *last_exit, int in_child);
void print_cmd_not_found(char *cmd);
void free_envp(char **envp);
void apply_heredoc_fd(t_node *node);
void execve_or_die(t_node *node, t_shell *sh, char *path);

int run_builtin(t_node *node, t_shell *sh, int *last_exit, int in_child);
int exec_external_cmd(t_node *node, t_shell *sh, int *last_exit);
int count_av(char **av);
char **dup_av(char **av);
t_node *alloc_copy_node(t_node *node);

#endif
