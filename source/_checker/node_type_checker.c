#include "../../include/minishell.h"

t_node_type check_token_type(char *str)
{
	if (!str)
		return (NODE_COMMAND);
	if (ft_strncmp(str, "|", 2) == 0)
		return (NODE_PIPE);
	if (ft_strncmp(str, ">", 2) == 0)
		return (NODE_RREDIRECT);
	if (ft_strncmp(str, "<", 2) == 0)
		return (NODE_LREDIRECT);
	if (ft_strncmp(str, ">>", 3) == 0)
		return (NODE_RSHIFT);
	if (ft_strncmp(str, "<<", 3) == 0)
		return (NODE_LSHIFT);
	if (ft_strncmp(str, "&&", 3) == 0)
		return (NODE_AND);
	if (ft_strncmp(str, "||", 3) == 0)
		return (NODE_OR);
	if (ft_strcmp(str, "(") == 0 || ft_strcmp(str, ")") == 0)
		return (NODE_GROUP);
	return (NODE_COMMAND);
}

const char *node_type_str(t_node_type type)
{
	switch (type)
	{
		case NODE_COMMAND: return "COMMAND";
		case NODE_PIPE: return "PIPE";
		case NODE_RREDIRECT: return ">";
		case NODE_LREDIRECT: return "<";
		case NODE_RSHIFT: return ">>";
		case NODE_LSHIFT: return "<<";
		case NODE_AND: return "&&";
		case NODE_OR: return "||";
		case NODE_GROUP: return "GROUP";
		default: return "UNKNOWN";
	}
}
