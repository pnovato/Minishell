#include "../../include/minishell.h"

char	*get_env_value(const char *key, t_env *env_list)
{
	while(env_list)
	{
		if(ft_strcmp(key, env_list->key) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*expand_env_variables(char *input, t_env *env_list, int last_exit)
{
	int	i = 0;
	int	j;
	char	*buffer;
	char	*result;
	char	*temp;	
	int	is_single_quote = 0;
	int	is_double_quote = 0;

	buffer = ft_strdup(input);
	result = ft_strdup("");
	while(buffer[i])
	{
		if (buffer[i] == '\'' && !is_double_quote)
			is_single_quote = !is_single_quote;
		else if (buffer[i] == '"' && !is_single_quote)
			is_double_quote = !is_double_quote;
		else if (buffer[i] == '$' && !is_single_quote)
		{
			if(buffer[i + 1] == '?')
			{
				char	*exit_str = ft_itoa(last_exit);
				temp = ft_strjoin(result, exit_str);
				free(result);
				free(exit_str);
				result = temp;	
				i++;
			}
			else
			{
				j = i + 1;
				while (ft_isalnum(buffer[j]) || buffer[j] == '_')
					j++;
				char	*var_name = ft_substr(buffer, i + 1, j - (i + 1));
				char	*value = get_env_value(var_name, env_list);
				free(var_name);
				if(!value)
					value = "";
				temp = ft_strjoin(result, value);
				free(result);
				result = temp;
				i = j - 1;
			}
		}
		else
		{
			char str[2] = {buffer[i], '\0'};
			temp = ft_strjoin(result, str);
			free(result);
			result = temp;
		}
		i++;
	}
	free(buffer);
	return (result);
}

void	expand_token_list(t_token *token_list, t_env *env_list, int last_exit)
{
	while (token_list)
	{
		if (token_list->type == NODE_COMMAND || token_list->type == NODE_FILENAME)
		{
			char *expanded = expand_env_variables(token_list->raw_value, env_list, last_exit);
			free(token_list->value);
			token_list->value = expanded;
		}
		token_list = token_list->next;
	}
}

void	remove_token_quotes(t_token *token)
{
	int		len;
	char	*stripped;

	while (token)
	{
		len = ft_strlen(token->value);
		if (len >= 2 &&
			((token->value[0] == '\'' && token->value[len - 1] == '\'') ||
			 (token->value[0] == '"' && token->value[len - 1] == '"')))
		{
			stripped = ft_substr(token->value, 1, len - 2);
			free(token->value);
			token->value = stripped;
		}
		token = token->next;
	}
}

