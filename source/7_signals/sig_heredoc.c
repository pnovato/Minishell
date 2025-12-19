#include "../../include/minishell.h"

void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	//g_signal_status = 130;
	close(STDIN_FILENO);
	g_signal_status = 130;
	rl_replace_line("", 0);
	rl_done = 1;
}

void	sigint_handler_main(int sig)
{
	(void)sig;
	g_signal_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

