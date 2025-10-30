#ifndef MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "../libft/libft.h"

typedef enum e_node_type
{
        NODE_COMMAND,
        NODE_PIPE,
        NODE_RREDIRECT,
	NODE_LREDIRECT,
	NODE_RSHIFT,
	NODE_LSHIFT,
	NODE_FILENAME,
        NODE_OR,
        NODE_AND,
        NODE_GROUP
}       t_node_type;

typedef struct s_node
{
	t_node_type	type;
	char		**av;
	char		*redirect_file;
	int		redirect_type;
	struct s_node	*left;
	struct s_node	*right;

}	t_node;

typedef struct s_token
{
	t_node_type	type;
	char		*value;
	struct s_token	*next;

}	t_token;

typedef struct s_quote
{
	bool	is_single;
	bool	is_double;
}	t_quote;

//essa estrutura é necessária pq vamos ter que ter o nosso proprio ambiente de execução.
//No subject tem umas built-ins:\"unset,export\" que se usarmos na envp[] normal, ela não executa
//pq não podemos modificar diretamente esse array (char **envp), quando precisamos modificar
//o ambiente na nossa minishell.
typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}	t_env;

// main.c
int main(int ac, char **av, char **envp);
void    print_env_list(t_env *env);
void	print_token_list(t_token *token);
void    minishell_loop(t_env *env_list, int last_exit);

// source/list_utils
t_env	*create_env_node(char *key, char *value);
void	free_env_list(t_env *env);

// source/1_pre_expansion
t_env   *envp_to_list(char **envp);

//source/2_expansion
char    *get_env_value(char *key, t_env *env_list);
char    *expand_env_variables(char *input, t_env *env_list, int last_exit);

//source/3_built_ins
void	handle_the_inputs(char *input, t_env *env_list);

//source/4_tokenization
t_token *split_line_to_token(char *line);
void    init_token_slice(t_token **lst, char *line, int start, int end);
void    token_add_back(t_token **lst, t_token *nw);
t_token *new_token(char *value, t_node_type type);

//source/_checker
void	check_quotes(char str, bool *is_single, bool *is_double);
bool	check_parenthesis_token(char *lin, int *i, int *s, t_token **l, t_quote *q);
bool	check_space_token(char *lin, int *i, int *s, t_token **l, t_quote *q);
bool	is_operator(char *str, int i);
t_node_type check_token_type(char *str);

//source/free
void	free_env_list(t_env *env);

#endif
