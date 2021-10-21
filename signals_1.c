# include "minishell.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("dfjk\n");
		rl_on_new_line();
		rl_line_buffer = 0;
		rl_point = 0;
		rl_end = 0;
		rl_redisplay();
	}
}

void	signal_receiver(void)
{
	struct sigaction	sa;

	sa.sa_handler = &sig_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
//	signal(SIGQUIT, SIG_IGN);
}
