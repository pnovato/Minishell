#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "../libft/libft.h"

typedef enum e_node_type
{
        NODE_COMMAND,
        NODE_PIPE,
        NODE_REDIRECT,
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

//essa estrutura é necessária pq vamos ter que ter o nosso proprio ambiente de execução.
//No subject tem umas built-ins:"unset,export" que se usarmos na envp[] normal, ela não executa
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

// source/list_utils
t_env	*create_env_node(char *key, char *value);

// source/pre_expansion
t_env   *envp_to_list(char **envp);
//Funcão que vai tratar de cada comando builtin
void	handle_the_inputs(char *input, t_env *env_list);

#endif
