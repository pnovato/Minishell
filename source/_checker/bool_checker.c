#include "../../include/minishell.h"

void	check_quotes(char str, bool *is_single, bool *is_double)
{
	if (str == '\'' && !(*is_double))
		*is_single = !(*is_single);
	else if (str == '"' && !(*is_single))
		*is_double = !(*is_double);
}


bool	check_parenthesis_token(char *lin, int *i, int *s, t_token **l, t_quote *q)
{
	check_quotes(lin[*i], &q->is_single, &q->is_double);
	
	if (!(q->is_single) && !(q->is_double)
		&& (lin[*i] == '(' || lin[*i] == ')'))
	{
		if (*i > *s)
			init_token_slice(l, lin, *s, *i);
		init_token_slice(l, lin, *i, *i + 1);
		(*i)++;
		while (lin[*i] == ' ')
			(*i)++;
		*s = *i;
		return (true);
	}
	return (false);
}

bool	check_space_token(char *lin, int *i, int *s, t_token **l, t_quote *q)
{
	if (!(q->is_single) && !(q->is_double) && lin[*i] == ' ')
	{
		if (*i > *s)
			init_token_slice(l, lin, *s, *i);
		while (lin[*i] == ' ')
			(*i)++;
		*s = *i;
		return (true);
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
