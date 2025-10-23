/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_key_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:35:51 by matheusless       #+#    #+#             */
/*   Updated: 2025/10/23 14:38:35 by matheusless      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

char	*join_key_value(const char *key, const char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, value);
	free(tmp);
	return (result);
}
