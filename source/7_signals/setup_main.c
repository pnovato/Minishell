#include "../../include/minishell.h"

void	setup_signals_main(void)
{
	signal(SIGINT, handle_sigint);
}
