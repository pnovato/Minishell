/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matheuslessa <matheuslessa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:23:50 by matheusless       #+#    #+#             */
/*   Updated: 2025/10/10 15:23:53 by matheusless      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	builtin_exit(char **args)
{
	(void)args;
	exit(0);
}
