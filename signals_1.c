# include "minishell.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		//printf("jnfg");
		rl_on_new_line();
		rl_line_buffer = 0;
		rl_point = 0;
		rl_end = 0;
		write(1, "\b\b", 2);
		write(1, "  ", 2);
		write(1, "\b\b\n", 3);
		rl_redisplay();
	}
}

/*Cambiar por sigaction y añadir la flag de ignorar la SIG_IGN para poder mutear los print*/
void	signal_receiver(void)
{
	struct sigaction	sa;

	sa.sa_handler = &sig_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
//	signal(SIGQUIT, SIG_IGN);
}
