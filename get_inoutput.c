#include "minishell.h"
int redirection_counter(char **token, char operator)
{
	int i;
	int j;
	int redirections;

	i = 0;
	redirections = 0;
	while (token && token[i])
	{
		j = 0;
		while (token[i][j])
		{
			if (token[i][j] == '\'' || token[i][j] == '"')
			{
				if (token[i][j] == '\'')
				{
					j++;
					while(token[i][j] && token[i][j] != '\'')
						j++;
				}
				else if (token[i][j] == '"')
				{
					j++;
					while (token[i][j] && token[i][j] != '"')
						j++;
				}
			}
			if (token[i][j] == operator && token[i][j + 1] != operator)
				redirections++;
			j++;
		}
		i++;
	}
	return (redirections);
}

char **ft_get_inputs(char ***token)
{
	char **new_token;
	char **fds;
	int i;
	int j;
	int b;

	i = redirection_counter(*token, '<'); /// contador de redirecciones;
	if (!i)
		return (NULL);
	fds = (char **)malloc(sizeof(char *) * (i + 1));
	if (!fds)
		return (NULL);
	while(token[0][i])
	{
		j = 0;
		while (token[0][i][j])
		{
			if (token[0][i][j] == '<' && token[0][i][j + 1] != '<')
			{
				//if (token[0][i][j + 1])
				//	fds[b] = ;
			}
			else if(token[0][i][j] == '<' && token[0][i][j + 1] == '<')
				j++;
			j++;
		}
		i++;
	}
	new_token = remove_ops_files(*token);
	return (fds);
}
/*  remove_ops_files(char **token):
	Esta función se encarga de remover tanto los operadores , 
	como los archivos despues a este y por lo tanto a modifica
	Ya que es complejo determinar las dimensiones de la "new_token" 
	lo mas sencillo es crear un nuevo string completo con todo, 
	excepto los operadores y el string singuiente a los operadores. */