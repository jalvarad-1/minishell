#include "minishell.h"
void move_out_quotes(char **token, int *i, int *j)
{
	if (!token || !token[*i])
		return ;
	if (token[*i][*j] == '\'' || token[*i][*j] == '"')
	{
		if (token[*i][*j] == '\'')
		{
			(*j)++;
			while(token[*i][*j] && token[*i][*j] != '\'')
				(*j)++;
		}
		else if (token[*i][*j] == '"')
		{
			(*j)++;
			while (token[*i][*j] && token[*i][*j] != '"')
				(*j)++;
		}
	}
}

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
			move_out_quotes(token, &i, &j);
			if (token[i][j] == operator && token[i][j + 1] != operator)
				redirections++;
			j++;
		}
		i++;
	}
	return (redirections);
}

int	fd_len(char *token)
{
	int	len;

	len = 0;
	while (token[len] && token[len] != '<' && token[len] != '>')
	{
		len++;
	}
	return (len);
}
char *save_fd_name(char **token, int *i, int *j)
{
	char	*fd_name;
	int		name_size;

	name_size = 0;
	while (token[*i])
	{
		while (token[*i][*j] && token[*i][*j] == ' ')
			(*j)++;
		if (token[*i][*j] && token[*i][*j] != ' ')
			break ;
		else
			(*i)++;
	}
	name_size = fd_len(token[*i] + *j);
	fd_name = ft_substr(token[*i], *j, name_size);
	return (fd_name);
}

char **remove_ops_files(char **token, char optr)
{
	char **nw_tk;
	char *ltt_tk;
	char *aux;

	while (token[i])
	{

		while()
	}

	
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
	b = 0;
	fds = (char **)malloc(sizeof(char *) * (i + 1));
	if (!fds)
		return (NULL);
	while(token[0][i])
	{
		j = 0;
		while (token[0][i][j])
		{
			move_out_quotes(token[0], &i, &j);
			if (token[0][i][j] == '<' && token[0][i][j + 1] != '<')
			{
				j++;
				fds[b] = save_fd_name(token[0], &i, &j);
				b++;
			}
			else if(token[0][i][j] == '<' && token[0][i][j + 1] == '<')
				j++;
			j++;
		}
		i++;
	}
	fds[b] = NULL;
	new_token = remove_ops_files(*token, '<');/* falta hacer esta función */
	return (fds);
}
/*  remove_ops_files(char **token):
	Esta función se encarga de remover tanto los operadores , 
	como los archivos despues a este y por lo tanto a modifica
	Ya que es complejo determinar las dimensiones de la "new_token" 
	lo mas sencillo es crear un nuevo string completo con todo, 
	excepto los operadores y el string singuiente a los operadores. */