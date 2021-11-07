# include "minishell.h"

void	sig_handler(int signal)
{
	(void)signal;
	if (g_common.pid == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_common.pid != 0)
	{
		kill(g_common.pid, SIGCONT);
		write(1, "\n", 1);
	}
	g_common.pid = 0;
//	write(1, "\b\b", 2);
//	write(1, "  ", 2);
}

/*Cambiar por sigaction y añadir la flag de ignorar la SIG_IGN para poder mutear los print*/
void	signal_receiver(void)
{
	signal(SIGINT, sig_handler);
//	signal(SIGQUIT, SIG_IGN);
}
