# include "minishell.h"

t_global g_common;

int main (int argc, char **argv, char **env)
{
	while (1)
	{
		char *str = readline (YELLOW"🌯 Burri_shell 🌯 "GREEN"> "RESET);
		free(str);
	}
}
