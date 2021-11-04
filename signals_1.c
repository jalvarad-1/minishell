# include "minishell.h"

void	sig_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
//	write(1, "\b\b", 2);
//	write(1, "  ", 2);
}

/*Cambiar por sigaction y añadir la flag de ignorar la SIG_IGN para poder mutear los print*/
void	signal_receiver(void)
{
	struct sigaction	sa;

	sa.sa_handler = &sig_handler;
	sa.sa_flags = SA_RESTART;
//	sigaction(SIGINT, &sa, NULL);
//	signal(SIGQUIT, SIG_IGN);
}
