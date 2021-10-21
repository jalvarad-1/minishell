# include "minishell.h"

t_global g_common;
HIST_ENTRY ** the_history_list;

char	*print_promt(void)
{
	char *str;

	str = readline("\1\033[0;32m\2Burri_shell> ");
	if (!str)
	{
		write(1, "\b\b", 2);
		exit(-1);
	}
	if (*str)
	{
		printf("|%s|", str);
		add_history(str);
	}

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
		//printf("|%s|", str);
		//if (str)
			//free(str);

	}
}
