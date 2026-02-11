/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:55:29 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 14:55:36 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	builtin_env(t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (curr->value)
		{
			ft_putstr_fd(curr->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(curr->value, 1);
			ft_putchar_fd('\n', 1);
		}
		curr = curr->next;
	}
	return (0);
}
