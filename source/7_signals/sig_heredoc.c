/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:35:32 by pnovato-          #+#    #+#             */
/*   Updated: 2026/01/15 15:35:36 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	g_signal_status = 130;
	write(1, "\n", 1);
}

void	sigint_handler_main(int sig)
{
	(void)sig;
	if (g_signal_status == 131)
	{
		g_signal_status = 130;
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	g_signal_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
