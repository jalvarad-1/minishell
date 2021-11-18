# include "minishell.h"

/*TODO MODIFICAR FUNCION PARA QUE DEVUELVS STRUCT DE INPUTS Y OUTPUTS*/
/*JUNTAR HEREDOC E INOUT EN UNA FUNCION*/
static int	ft_get_n_heredoc(char **token, char opr)
{
	int		i;
	int		j;
	int		c;

	i = 0;
	c = 0;
	while (token[i])
	{
		j = 0;
		while (token[i][j])
		{
			move_out_quotes(token, i, &j);
			if (token[i][j] == opr)
			{
				j++;
				if (token[i][j] == opr)
					c++;
			}
			j++;
		}
		i++;
	}
	return (c);
}

char	*save_h_cmd(char **token, int *i)
{
	if (token[*i - 1])
		return (token[*i - 1]);
	return(token[++(*i)]);
}

char	**get_heredoc_input(char ***token, char opr)
{
	int		i;
	int		j;
	int		b;
	char	**fds;
	char	**new_token;

	b = ft_get_n_heredoc(*token, opr);
	if (!b)
		return (NULL);
	fds = ft_calloc(sizeof(char *), b + 1);
	if (!fds)
		return (NULL);
	i = 0;
	b = 0;
	while(token[0][i])
	{
		j = 0;
		while (token[0][i][j])
		{
			move_out_quotes(token[0], i, &j);
			if (token[0][i][j] == opr)
			{
				j++;
				if (token[0][i][j] == opr)
				{
					if (token[0][i][++j])
					{
						fds[b] = save_fd_name(token[0], &i, &j);
						b++;
						fds[b] = save_h_cmd(token[0], &i);
					}
					else
					{
						i++;
						j = 0;
						fds[b] = save_fd_name(token[0], &i, &j);
						b++;
						fds[b] = save_h_cmd(token[0], &i);
					}
				}
			}
			j++;
		}
		i++;
	}
	fds[b] = NULL;
	new_token = remove_ops_files(*token, opr);
	free_matrix(*token);
	*token = new_token;
	return (fds);

}
