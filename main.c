# include "minishell.h"

t_global g_common;
HIST_ENTRY ** the_history_list;

char	*print_promt(void)
{
	char *str;


	str = readline("Burri_shell > ");
	if (!str)
	{
		write(1, "\b\b", 2);
		exit(-1);
	}

	if (*str)
		add_history(str);
	return (str);
}

int main (int argc, char **argv, char **envp)
{
	char *str;

	str = NULL;
	signal_receiver();
	while (1)
	{
		str = print_promt();
		if (ft_strcmp(str, ""))
		{
			built_in_identifier(str);
		}
		free(str);
	}
}
