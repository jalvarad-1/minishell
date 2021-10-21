# include "minishell.h"

t_global g_common;

char	*print_promt(void)
{
	char *str;

	str = readline(YELLOW"🌯 Burri_shell 🌯 "GREEN"> "RESET);
	if (*str)
		add_history(str);
	return (str);
}

int main (void)
{
	char *str;

	str = NULL;
	signal_receiver();
	while (1)
	{
		str = print_promt();
		built_in_identifier(str);
		if (str)
			free(str);
	}
}
