#include "../../include/minishell.h"

bool	check_quotes(char str, bool *is_single, bool *is_double)
{
	if (str == '\'' && !(*is_double))
	{
		*is_single = !(*is_single);
		return (*is_single);
	}
	else if (str == '"' && !(*is_single))
	{
		*is_double = !(*is_double);
		return (*is_double);
	}
	return (false);
}	

bool	is_operator(char *str, int i)
{
	if (str[i] == '|')
		return (true);
	else if (str[i] == '>')
		return (true);
	else if (str[i] == '<')
		return (true);
	else if (str[i] == '>' && str[i+1] == '>')
		return (true);
	else if (str[i] == '<' && str[i+1] == '<')
		return (true);
	else if (str[i] == '&' && str[i+1] == '&')
		return (true);
	else if (str[i] == '|' && str[i+1] == '|')
		return (true);
	return (false);
}
