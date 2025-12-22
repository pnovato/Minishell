#include "../../include/minishell.h"

void	setup_signals_main(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sigint_handler_main;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	setup_signals_child(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigaction(SIGINT,  &sa, NULL);
}

void	setup_signals_heredoc(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = sigint_handler_heredoc;
	sa_int.sa_flags = 0;

	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;

	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL); 

}

void setup_signals_waiting(void)
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}

void setup_signals_heredoc_child(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_handler = SIG_DFL;
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);

    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_handler = SIG_IGN;
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}

