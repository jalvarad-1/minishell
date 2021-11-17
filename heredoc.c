# include "minishell.h"

void	pipex_for_heredoc(t_cmds *cmds)
{
	char	*str;

	str = NULL;
	while (1)
	{
		str = readline(">");
		if (ft_strcmp(str, table->heredoc_end[0]))
			break ;
		//enviar a table->heredoc_end[1];
		free(str);
	}
	if (str)
		free(str);
}


// La idea seria tener una estatica i = 0. i + 1 seria el comando al que va dirigido.
// Si no toca cambiar las funciones para que guarden bien las cosas
void	ft_heredoc(t_cmds *table)
{
	char	*str;

	str = NULL;
	if (!table->heredoc_end[1])
	{
		while (1)
		{
			str = readline(">");
			if (ft_strcmp(str, table->heredoc_end[0]))
				break ;
			free(str);
		}
		if (str)
			free(str);
	}
	else
		pipex_for_heredoc(table);
}
