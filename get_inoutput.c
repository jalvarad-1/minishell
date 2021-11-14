#include "minishell.h"

void	move_out_quotes(char **token, int i, int *j)
{
	if (!token || !token[i])
		return ;
	if (token[i][*j] == '\'' || token[i][*j] == '"')
	{
		if (token[i][*j] == '\'')
		{
			(*j)++;
			while(token[i][*j] && token[i][*j] != '\'')
				(*j)++;
		}
		else if (token[i][*j] == '"')
		{
			(*j)++;
			while (token[i][*j] && token[i][*j] != '"')
				(*j)++;
		}
	}
}

int	redirection_counter(char **token, char operator)
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
			move_out_quotes(token, i, &j);
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

void mod_move_out_quotes(char *token, int *i)
{
	if (!token || !token[*i])
		return ;
	if (token[*i] == '\'' || token[*i]== '"')
	{
		if (token[*i] == '\'')
		{
			token[*i] = ' ';
			(*i)++;
			while(token[*i] && token[*i] != '\'')
			{
				token[*i] = ' ';
				(*i)++;
			}
		}
		else if (token[*i] == '"')
		{
			token[*i] = ' ';
			(*i)++;
			while (token[*i] && token[*i] != '"')
			{
				token[*i] = ' ';
				(*i)++;
			}
		}
	}
}

char *token_in_one_str(char **token, char optr)
{
	char	*ltt_tk;
	char	*aux;
	int		i;

	i = 0;
	ltt_tk = ft_strjoin(token[i], " ");
	while (token[++i])
	{
		aux = ft_strjoin(ltt_tk, token[i]);
		free(ltt_tk);
		ltt_tk = ft_strjoin(aux, " ");
		free(aux);
	}
	i = 0;
	while (ltt_tk[i])
	{
		move_out_quotes(&ltt_tk, 0, &i);
		if (ltt_tk[i] == optr)
		{
			ltt_tk[i] = ' ';
			while (ltt_tk[i] && ltt_tk[i] == ' ')
				i++;
			while (ltt_tk[i] && ltt_tk[i] != ' ')
			{
				mod_move_out_quotes(ltt_tk, &i);
				ltt_tk[i++] = ' ';
			}
		}
		i++;
	}
	return (ltt_tk);
}

char **remove_ops_files(char **token, char optr)
{
	char **nw_tk;
	char *ltt_tk;

	ltt_tk = token_in_one_str(token, optr);
	nw_tk = ft_mod_split(ltt_tk,' ');
	free (ltt_tk);
	return (nw_tk);
}

char **ft_get_inputs(char ***token, char oprt)
{
	char **new_token;
	char **fds;
	int i;
	int j;
	int b;

	i = redirection_counter(*token, oprt); /// contador de redirecciones;
	if (!i)
		return (NULL);
	b = 0;
	fds = (char **)malloc(sizeof(char *) * (i + 1));
	if (!fds)
		return (NULL);
	i = 0;
	while(token[0][i])
	{
		j = 0;
		while (token[0][i][j])
		{
			move_out_quotes(token[0], i, &j);
			if (token[0][i][j] == '<' && token[0][i][j + 1] != '<')
			{
				if (token[0][i][++j])
				{
					fds[b] = save_fd_name(token[0], &i, &j);
					b++;
				}
				else
				{
					i++;
					j = 0;
					fds[b] = save_fd_name(token[0], &i, &j);
					b++;
				}
			}
			else if(token[0][i][j] == '<' && token[0][i][j + 1] == '<')
				j++;
			j++;
		}
		i++;
	}
	fds[b] = NULL;
	new_token = remove_ops_files(*token, '<');
	free_matrix(*token);
	*token = new_token;
	return (fds);
}
/*  remove_ops_files(char **token):
	Esta función se encarga de remover tanto los operadores ,
	como los archivos despues a este y por lo tanto a modifica
	Ya que es complejo determinar las dimensiones de la "new_token"
	lo mas sencillo es crear un nuevo string completo con todo,
	excepto los operadores y el string singuiente a los operadores. */
