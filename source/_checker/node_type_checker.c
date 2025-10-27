#include "../../include/minishel.h"


#include <../../include/minishell.h>

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
}
