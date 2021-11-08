# include "minishell.h"

void	sig_handler(int signal)
{
	(void)signal;
	if(g_common.pid == 0)
		write(1, "\n", 1);
	if (!g_common.is_cmd)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
//	write(1, "\b\b", 2);
//	write(1, "  ", 2);
}

//TODO IMPLEMENTAR EL METODO DE TOMAS : CAMBIAR EL COMPORTAMIENTOS DE LAS SEÑALES A SIG_DFLT CUANDO ENTRAN AL PIPE Y LUEGO RESTAURAR.
//TODO DE ESTA MANERA ES SOLO EL HIJO EL QUE LAS INTERPRETA SIN NECESIDAD DE VARIABLE GLOBAL
void	signal_receiver(void)
{
	struct sigaction	sa;

	sa.sa_handler = &sig_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
//	signal(SIGQUIT, SIG_IGN);
}
