#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include "execution.h"
#include "builtins.h"

extern int g_signal_status;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_RREDIRECT,
	NODE_LREDIRECT,
	NODE_APPEND,
	NODE_HEREDOC,
	NODE_FILENAME,
	NODE_OR,
	NODE_AND,
	NODE_GROUP
} t_node_type;

typedef struct s_node
{
	t_node_type type;
	char **av;
	char *redirect_file;
	int redirect_type;
	int heredoc_fd;
	int heredoc_expand;
	struct s_node *left;
	struct s_node *right;
} t_node;

typedef struct s_token
{
	t_node_type type;
	char *value;
	char *raw_value;
	struct s_token *next;
} t_token;

typedef struct s_quote
{
	bool is_single;
	bool is_double;
} t_quote;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_shell
{
	t_node *ast;
	t_token *tokens;
	t_env *env;
	char *line;

	int stdin_bkp;
	int stdout_bkp;
	int stderr_bkp;
} t_shell;

// main.c
int main(int ac, char **av, char **envp);
void print_env_list(t_env *env);
void print_token_list(t_token *token);
void minishell_loop(t_env *env_list, int *last_exit);
void print_ast(t_node *node, int depth);

// source/list_utils
t_env *create_env_node(char *key, char *value);
void free_env_list(t_env *env);
void free_token(t_token *t);
void free_token_list(t_token *token);
void free_ast(t_node *node);
void free_line(char **line);
void free_tokens(t_token **tokens);
void free_ast_ptr(t_node **ast);
void free_env_ptr(t_env **env);

// source/1_pre_expansion
t_env *envp_to_list(char **envp);

// source/2_expansion
char *get_env_value(const char *key, t_env *env_list);
char *expand_env_variables(char *input, t_env *env_list, int last_exit);
int env_size(t_env *env);
void append_to_result(char **result, const char *add);
void append_char_to_result(char **result, char c);
void expand_exit_status(char **result, int last_exit);
void expand_named_var(char **result, char *buf, int *i, t_env *env_list);
void update_quotes(char c, int *sq, int *dq);
void handle_dollar(char **result, char *buf, int *i,
				   t_env *env_list, int last_exit);
void expand_token_list(t_token *token_list, t_env *env_list, int last_exit);
void remove_token_quotes(t_token *token);

// source/4_tokenization
t_token *split_line_to_token(char *line);
void init_token_slice(t_token **lst, char *line, int start, int end);
void token_add_back(t_token **lst, t_token *nw);
t_token *new_token(char *value, t_node_type type);
char **token_list_to_args(t_token *token);
void token_add_back(t_token **lst, t_token *nw);
void free_args_partial(char **args, int count);
int token_count(t_token *tok);

// source/5_parsing
t_node *build_ast(t_token *start, t_token *end);
t_node *alloc_type(t_token *start, t_token *end, t_token *op);
char **token_op_to_args(t_token *start, t_token *end);
t_token *ft_lstlast_token(t_token *token);
t_token *find_last_operator(t_token *start, t_token *end);
t_token *op_before(t_token *start, t_token *target);
t_node *new_cmd_node(char **args);
t_node *new_op_node(t_node_type type);
t_node *build_redirect_node(t_node *node, t_token *start,
							t_token *op_prev, t_token *op_next);
t_node *build_pipe_node(t_node *node, t_token *start,
						t_token *op_prev, t_token *op_next, t_token *end);
int is_redirect_type(t_node_type type);
int is_cmd_token(t_token *tok);
int count_cmd_tokens(t_token *start, t_token *end);
int fill_args(char **args, t_token *start, t_token *end);
void remove_one_token_quotes(t_token *token);

// source/7_signals
void handle_sigint(int sig);
void setup_signals_main(void);
void setup_signals_child(void);
void setup_signals_heredoc(void);
void sigint_handler_heredoc(int sig);
void sigint_handler_main(int sig);
void setup_signals_waiting(void);
void setup_signals_heredoc_child(void);
// void	enable_echoctl(void);

// source/_checker
void check_quotes(char str, bool *is_single, bool *is_double);
bool check_parenthesis_token(char *lin, int *i, int *s, t_token **l, t_quote *q);
bool check_space_token(char *lin, int *i, int *s, t_token **l, t_quote *q);
bool is_operator(char *str, int i);
t_node_type check_token_type(char *str);
bool has_operator(t_token *token);
const char *node_type_str(t_node_type type);

#endif
