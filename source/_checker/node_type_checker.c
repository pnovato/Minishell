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
		return (NODE_APPEND);
	if (ft_strncmp(str, "<<", 3) == 0)
		return (NODE_HEREDOC);
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
	if (type == NODE_COMMAND)
		return ("COMMAND");
	if (type == NODE_PIPE)
		return ("|");
	if (type == NODE_RREDIRECT)
		return ("NODE_RREDIRECT");
	if (type == NODE_LREDIRECT)
		return ("NODE_LREDIRECT");
	if (type == NODE_APPEND)
		return ("NODE_APPEND");
	if (type == NODE_HEREDOC)
		return ("NODE_HEREDOC");
	if (type == NODE_AND)
		return ("NODE_AND");
	if (type == NODE_OR)
		return ("NODE_OR");
	if (type == NODE_GROUP)
		return ("NODE_GROUP");
	else
		return ("UNKNOWN");
}
