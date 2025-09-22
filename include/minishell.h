#ifndef MINISHELL_H
# include <stdio.h>

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

int main();

#endif
