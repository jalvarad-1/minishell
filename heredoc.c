# include "minishell.h"

void	pipex_for_heredoc(t_cmds *cmds)
{
	char	*str;
	char	*aux;
	char	*pre_aux;

	str = NULL;
	while (1)
	{
		while (1)
		{
			str = readline(">");
			if (ft_strcmp(str, table->heredoc_end[0]))
				break ;
			aux = ft_strjoin(str, pre_aux);
			pre_aux = str;
			free(str);
		}
		//Redireccionar aux por algun lado
		if (str)
			free(str);
		if (aux)
			free(aux);
}


// La idea seria tener una estatica i = 0. i + 1 seria el comando al que va dirigido.
// Si no toca cambiar las funciones para que guarden bien las cosas
void	ft_heredoc(t_cmds *table)
{
	char	*str;
	char	*aux;
	char	*pre_aux;

	str = NULL;
	pre_aux = NULL;
	if (!table->heredoc_end[1])
	{
		while (1)
		{
			str = readline(">");
			if (ft_strcmp(str, table->heredoc_end[0]))
				break ;
			aux = ft_strjoin(str, pre_aux);
			pre_aux = str;
			free(str);
		}
		if (str)
			free(str);
		if (aux)
			free(aux);
	}
	else
		pipex_for_heredoc(table);
}
