/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:50:35 by matheusless       #+#    #+#             */
/*   Updated: 2025/10/23 16:02:16 by matheusless      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_value(t_env *env_list, const char *key)
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
				char	*value = get_env_value(env_list, var_name);
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
