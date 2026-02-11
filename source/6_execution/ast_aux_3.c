/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_aux_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:23:04 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 15:23:08 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_builtin(t_node *node, t_shell *sh, int *last_exit, int in_child)
{
	*last_exit = execute_builtin(node->av, sh->env, sh);
	if (in_child)
	{
		cleanup_child_min(sh->ast, sh->tokens, sh->env, sh->line);
		_exit(*last_exit);
	}
	return (*last_exit);
}

int	exec_external_cmd(t_node *node, t_shell *sh, int *last_exit)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = resolve_path(node->av[0], sh->env);
	if (!path)
		return (print_cmd_not_found(node->av[0]), *last_exit = 127, 127);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), free(path), 1);
	if (pid == 0)
		execve_or_die(node, sh, path);
	waitpid(pid, &status, 0);
	free(path);
	if (WIFEXITED(status))
		*last_exit = 128 + WTERMSIG(status);
	else
		*last_exit = 1;
	return (*last_exit);
}

int	count_av(char **av)
{
	int	i;

	i = 0;
	while (av && av[i])
		i++;
	return (i);
}

char	**dup_av(char **av)
{
	char	**new_av;
	int		i;
	int		n;

	n = count_av(av);
	new_av = malloc(sizeof(char *) * (n + 1));
	if (!new_av)
		return (NULL);
	i = 0;
	while (i < n)
	{
		new_av[i] = ft_strdup(av[i]);
		if (!new_av[i])
			return (free_envp(new_av), NULL);
		i++;
	}
	new_av[i] = NULL;
	return (new_av);
}

t_node	*alloc_copy_node(t_node *node)
{
	t_node	*new;

	new = ft_calloc(1, sizeof(t_node));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_node));
	new->type = node->type;
	new->heredoc_fd = node->heredoc_fd;
	if (node->redirect_file)
		new->redirect_file = ft_strdup(node->redirect_file);
	else
		new->redirect_file = NULL;
	return (new);
}
