#ifndef MINISHELL_H

typedef struct s_node
{
	int	data;	
	struct s_node *left_leaf;
	struct s_node *right_leaf;

}	t_node;

typedef struct s_arvore
{
	t_node *root;
}	t_arvore;




#endif
