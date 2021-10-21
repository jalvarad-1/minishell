# include "minishell.h"

t_global g_common;

void	print_promt(void)
{
	char *str;

	str = readline(YELLOW"🌯 Burri_shell 🌯 "GREEN"> "RESET);
	free(str);
}

int main (int argc, char **argv, char **env)
{
	signal_receiver();
	while (1)
	{
		print_promt();
	}
}
