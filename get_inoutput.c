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

static int	redirection_counter(char **token, char opr)
{
	int i;
	int j;
	int rdc;

	i = 0;
	rdc = 0;
	while (token[i])
	{
		j = 0;
		while (token[i][j])
		{
			move_out_quotes(token, i, &j);
			if (token[i][j] == opr)
			{
				rdc++;
				while (token[i][j] == opr)
					j++;
			}
			if (token[i][j])
				j++;
		}
		i++;
	}
	return (rdc);
}

static int	fd_len(char *token)
{
	int	len;

	len = 0;
	while (token[len] && token[len] != '<' && token[len] != '>')
		len++;
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

static void mod_move_out_quotes(char *token, int *i)
{
	printf("Entro y peto %d\n", *i);
	if (!token || !token[*i])
		return ;
	if (token[*i] == '\'' || token[*i] == '"')
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

static char *token_in_one_str(char **token, char opr)
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
		printf("%s \n", ltt_tk);
		mod_move_out_quotes(ltt_tk, &i);
		while (ltt_tk[i] == opr)
		{
			ltt_tk[i] = ' ';
			i++;
		}
		i++;
	}
	return (ltt_tk);
}

char **remove_ops_files(char **token, char opr)
{
	char **nw_tk;
	char *ltt_tk;

	ltt_tk = token_in_one_str(token, opr);
	nw_tk = ft_mod_split(ltt_tk, ' ');
	free (ltt_tk);
	return (nw_tk);
}

char	*do_heredoc(char **token, int *i, int *j)
{
	*j += 1;
	if (!token[*i][*j])
	{
		i++;
		return (save_fd_name(token, i, j));
	}
	else
		return (save_fd_name(token, i, j));
}

t_fds *ft_get_inputs(char ***token, char opr)
{
	char	**new_token;
	t_fds	*fds;
	int		i;
	int		j;
	int		b;

	i = redirection_counter(*token, opr); /// contador de redirecciones;
	if (!i)
		return (NULL);
	b = 0;
	fds = malloc(sizeof(t_fds) * (i + 1));
	if (!fds)
		return (NULL);
	i = 0;
	while(token[0][i])
	{
		j = 0;
		move_out_quotes(token[0], i, &j);
		if(token[0][i][j] == opr)
		{
			if (token[0][i][++j])
			{
				if (token[0][i][j] == opr)
				{
					j++;
					fds[b].fds = save_fd_name(token[0], &i, &j);
					if (opr == '<')
						fds[b].is_hdoc = 1;
					else
						fds[b].is_hdoc = 0;
				}
				else
				{
					fds[b].fds = save_fd_name(token[0], &i, &j);
					fds[b].is_hdoc = 0;
				}
				b++;
			}
			else
			{
				i++;
				j = 0;
				fds[b].fds = save_fd_name(token[0], &i, &j);
				fds[b].is_hdoc = 0;
				b++;
			}
			j++;
		}
		i++;
	}
//	fds[b] = NULL;
	printf("Llego \n");
	new_token = remove_ops_files(*token, opr);
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
