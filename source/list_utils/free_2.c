/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:38:37 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 15:38:52 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_ast(t_node *node)
{
	int	i;

	if (!node)
		return ;
	if (node->av)
	{
		i = 0;
		while (node->av[i])
		{
			free(node->av[i]);
			i++;
		}
		free(node->av);
	}
	if (node->redirect_file)
		free(node->redirect_file);
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

void	free_line(char **line)
{
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
}

void	free_ast_ptr(t_node **ast)
{
	if (!ast || !*ast)
		return ;
	free_ast(*ast);
	*ast = NULL;
}
