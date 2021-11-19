# include "minishell.h"
void	heredoc_doer(char *pre_aux)
{
	int		fd[2];

	pipe(fd);
	ft_putstr_fd(pre_aux, fd[WRITE_END]);
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
}
// La idea seria tener una estatica i = 0. i + 1 seria el comando al que va dirigido.
// Si no toca cambiar las funciones para que guarden bien las cosas
void	ft_heredoc(char *table)
{
	char	*str;
	char	*aux;
	char	*pre_aux;

	str = NULL;
	aux = NULL;
	pre_aux = NULL;
	if (table)
	{
		while (1)
		{
			str = readline(">");
			if (!str || !ft_strcmp(str, table))
				break ;
			aux = ft_strjoin(pre_aux, str);
			if (pre_aux)
			{
				free(pre_aux);
				pre_aux = NULL;
				free(str);
				str = NULL;
			}
			pre_aux = ft_strjoin(aux, "\n");
		}
		if (str)
			free(str);
		if (aux)
			free(aux);
	}
	heredoc_doer(pre_aux);
}