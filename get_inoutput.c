#include "minishell.h"

static int	redirection_counter(char **token, char opr)
{
	int	i;
	int	j;
	int	rdc;

	i = 0;
	rdc = 0;
	while (token && token[i])
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
	{
		if (token[len] == '"')
		{
			len++;
			while (token[len] != '"' && token[len])
				len++;
		}
		else if (token[len] == '\'')
		{
			len++;
			while (token[len] != '\'' && token[len])
				len++;
		}
		dprintf(2, "%d %c\n", len, token[len]);
		len++;
	}
	return (len);
}

char	*save_fd_name(char **token, int *i, int *j, char **env)
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
	ft_expand(&token[*i], env, 1);
	fd_name = ft_substr(token[*i], *j, name_size);
	return (fd_name);
}

char	*save_hdoc_end(char **token, int *i, t_fds *fds)
{
	char	*end;
	int		j;

	j = 0;
	while (token[*i][j] == '<')
		j++;
	if (ft_trim_quotes(&token[*i], 1))
		fds->expand = 1;
	else
		fds->expand = 0;
	end = ft_substr(token[*i], j, ft_strlen(token[*i]));
	fds->is_hdoc = 1;
	return (end);
}

static void	mod_move_out_quotes(char *token, int *i)
{
	if (!token || !token[*i])
		return ;
	if (token[*i] == '\'' || token[*i] == '"')
	{
		if (token[*i] == '\'')
		{
			token[*i] = ' ';
			(*i)++;
			while (token[*i] && token[*i] != '\'')
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

static void	aux_token_in_one_str(char *ltt_tk, char optr)
{
	int	i;

	i = 0;
	while (ltt_tk[i])
	{
		move_out_quotes(&ltt_tk, 0, &i);
		if (ltt_tk[i] == optr)
		{
			while (ltt_tk[i] == optr)
			{
				ltt_tk[i] = ' ';
				i++;
			}
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
}

static char	*token_in_one_str(char **token, char optr)
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
	aux_token_in_one_str(ltt_tk, optr);
	return (ltt_tk);
}

char	**remove_ops_files(char **token, char opr)
{
	char	**nw_tk;
	char	*ltt_tk;

	ltt_tk = token_in_one_str(token, opr);
	nw_tk = ft_mod_split(ltt_tk, ' ');
	free (ltt_tk);
	return (nw_tk);
}

static void	aux_get_inputs(char **token, char opr, char **env, t_fds *fds)
{
	int	i;
	int j;
	int b;

	b = 0;
	i = 0;
	while (token[i])
	{
		j = 0;
		move_out_quotes(token, i, &j);
		while (token[i][j])
		{
			if (token[i][j] == opr)
			{
				if (token[i][++j])
				{
					if (token[i][j++] == opr)
					{
						if (!token[i][j])
						{
							i++;
							j = 0;
						}
						if (opr == '<')
						{
							fds[b].fds = save_hdoc_end(token, &i, &fds[b]);
						}
						else if (opr == '>')
							fds[b]= (t_fds){save_fd_name(token, &i, &j, env), 1, 0};
					}
					else
						fds[b] = (t_fds){save_fd_name(token, &i, &j, env), 0, 0};
				}
				else
				{
					i++;
					j = 0;
					fds[b] = (t_fds){save_fd_name(token, &i, &j, env), 0, 0};
				}
				b++;
			}
			j++;
		}
		i++;
	}
	fds[b].fds = NULL;
}

t_fds	*ft_get_inputs(char ***token, char opr, char **env)
{
	char	**new_token;
	t_fds	*fds;
	int		i;
	int		b;

	i = redirection_counter(*token, opr);
	if (!i)
		return (NULL);
	b = 0;
	fds = malloc(sizeof(t_fds) * (i + 1));
	if (!fds)
		return (NULL);
	aux_get_inputs(token[0], opr, env, fds);
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
