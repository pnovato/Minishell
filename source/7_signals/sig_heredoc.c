#include "../../include/minishell.h"

void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	//write(STDOUT_FILENO, "\n", 1);
	//g_signal_status = 130;
	//close(STDIN_FILENO);
	g_signal_status = 130;
	//rl_replace_line("", 0);
	//rl_done = 1;
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
		return;
	}
	g_signal_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();	
	rl_redisplay();
}

/*void enable_echoctl(void)
{
    struct termios term;

    if (tcgetattr(STDIN_FILENO, &term) == -1)
        return;

    term.c_lflag |= ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}*/
