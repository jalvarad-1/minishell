#include "minishell.h"

static int	redirection_counter(char **token, char opr)
{
	t_iterator	i;

	i = (t_iterator){0, 0, 0, 0};
	while (token && token[i.i])
	{
		i.j = 0;
		while (token[i.i][i.j])
		{
			move_out_quotes(token, i.i, &i.j);
			if (token[i.i][i.j] == opr)
			{
				i.b++;
				while (token[i.i][i.j] == opr)
					i.j++;
			}
			if (token[i.i][i.j])
				i.j++;
		}
		i.i++;
	}
	return (i.b);
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
		len++;
	}
	return (len);
}

char	*save_fd(char **token, int *i, int *j, char **env)
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
			token[(*i)++] = ' ';
			while (token[*i] && token[*i] != '\'')
				token[(*i)++] = ' ';
		}
		else if (token[*i] == '"')
		{
			token[(*i)++] = ' ';
			while (token[*i] && token[*i] != '"')
				token[(*i)++] = ' ';
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

static void	found_opr_case(char **token, char **env, t_fds *fds, t_iterator *i)
{
	if (token[i->i][++i->j])
	{
		if (token[i->i][i->j++] == i->opr)
		{
			if (!token[i->i][i->j])
			{
				i->i++;
				i->j = 0;
			}
			if (i->opr == '<')
				fds[i->b].fds = save_hdoc_end(token, &i->i, &fds[i->b]);
			else if (i->opr == '>')
				fds[i->b] = (t_fds){save_fd(token, &i->i, &i->j, env), 1, 0};
		}
		else
			fds[i->b] = (t_fds){save_fd(token, &i->i, &i->j, env), 0, 0};
	}
	else
	{
		i->i++;
		i->j = 0;
		fds[i->b] = (t_fds){save_fd(token, &i->i, &i->j, env), 0, 0};
	}
}

static void	aux_get_inputs(char **token, char opr, char **env, t_fds *fds)
{
	t_iterator	i;

	i = (t_iterator){0, 0, 0, opr};
	while (token[i.i])
	{
		i.j = 0;
		move_out_quotes(token, i.i, &i.j);
		while (token[i.i][i.j])
		{
			if (token[i.i][i.j] == opr)
			{
				found_opr_case(token, env, fds, &i);
				i.b++;
			}
			i.j++;
		}
		i.i++;
	}
	fds[i.b].fds = NULL;
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
