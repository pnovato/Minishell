#include "../../include/minishell.h"

void	ft_lstadd_back_token(t_list **token, char *str, int start, int len)
{
	t_list	*new;
	
	new = ft_lstnew(ft_substr(str, start, len));
	if (!new)
		return;
	ft_lstadd_back(token, new);
} 

void	before_after_op(char *line, t_list **token, int *i, int *start)
{
	int	len;
	
	len = (line[*i+1] == line[*i]) ? 2 : 1;
	ft_lstadd_back_token(token, line, *i, len);
	*i += len;
	while (line[*i] == ' ')
		(*i)++;
	*start = *i;
}

char	**split_line_to_token(char *line)
{
	t_list	*token;
	int	i;
	int	start;
	bool	is_single;
	bool	is_double;
	
	i = 0;
	start = 0;
	token = NULL;
	is_single = false;
	is_double = false;
	while (line[i])
	{
		check_quotes(line[i], &is_single, &is_double);
		if (!is_single && !is_double && is_operator(line, i))
		{	
			if (i > start)
				ft_lstadd_back_token(&token, line, start, i - start);
			before_after_op(line, &token, &i, &start);
			continue;
		}
		i++;		
	}
	if (i > start)
		ft_lstadd_back_token(&token, line, start, i - start);
	print_token_list(token);
	return (NULL/*lst_of_tokens(token)*/);
}
