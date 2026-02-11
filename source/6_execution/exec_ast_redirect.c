/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:25:37 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 15:25:54 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_redirect(t_node *node, t_shell *sh, int *last_exit, int in_child)
{
	int	fd;
	int	saved_in;
	int	saved_out;
	int	code;

	if (!node || !node->left)
		return (*last_exit = 1);
	fd = open_redirect_fd(node);
	if (fd < 0)
		return (perror("open"), *last_exit = 1);
	saved_in = -1;
	saved_out = -1;
	if (!in_child)
		save_std_fds(node, &saved_in, &saved_out);
	apply_redirect(node, fd);
	close(fd);
	code = exec_ast(node->left, sh, last_exit, in_child);
	if (!in_child)
		restore_std_fds(saved_in, saved_out);
	if (in_child)
		exit(code);
	return (code);
}
