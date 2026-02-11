/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:31:06 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 15:31:59 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_redirect_fd(t_node *node)
{
	if (node->heredoc_fd > 0)
		return (node->heredoc_fd);
	if (node->type == NODE_RREDIRECT)
		return (open(node->redirect_file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (node->type == NODE_LREDIRECT)
		return (open(node->redirect_file, O_RDONLY));
	if (node->type == NODE_APPEND)
		return (open(node->redirect_file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
}

int	is_input_redirect(t_node *node)
{
	if (node->type == NODE_LREDIRECT)
		return (1);
	if (node->heredoc_fd > 0)
		return (1);
	return (0);
}

void	save_std_fds(t_node *node, int *saved_in, int *saved_out)
{
	if (is_input_redirect(node))
		*saved_in = dup(STDIN_FILENO);
	else
		*saved_out = dup(STDOUT_FILENO);
}

void	restore_std_fds(int saved_in, int saved_out)
{
	if (saved_in != -1)
	{
		dup2(saved_in, STDIN_FILENO);
		close(saved_in);
	}
	if (saved_out != -1)
	{
		dup2(saved_out, STDOUT_FILENO);
		close(saved_out);
	}
}

void	apply_redirect(t_node *node, int fd)
{
	if (is_input_redirect(node))
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
}
