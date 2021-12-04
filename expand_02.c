#include "minishell.h"

size_t	*get_pos_dollar(size_t j, t_parse *prs, size_t **pos)
{
	size_t	*aux;
	size_t	i;

	i = 0;
	aux = malloc(sizeof(size_t) * prs->n_dollar);
	if (!aux)
		return (0);
	while (i < prs->n_dollar - 1)
	{
		aux[i] = (*pos)[i];
		i++;
	}
	aux[i] = j;
//	if (*pos)
//		free(*pos);
	return (aux);
}

void	ft_dollar_expand(char **str, char **env, t_parse prs)
{
	char	**aux;
	size_t	i;
	size_t	j;

	aux = ft_calloc(sizeof(char *), prs.n_dollar + 1);
	if (!aux)
		return ;
	i = 0;
	while (i < prs.n_dollar)
	{
		j = 0;
		while (((*str)[prs.pos_dollar[i] + j] && (*str)[prs.pos_dollar[i] + j] != ' ')
				&& (*str)[prs.pos_dollar[i] + j] != '$' && (*str)[prs.pos_dollar[i] + j] != '"'
				&& (*str)[prs.pos_dollar[i] + j] != '\'')
			j++;
		aux[i] = ft_substr(*str, prs.pos_dollar[i], j);
		i++;
	}
	ft_seek_env(str, env, aux);
	free_matrix(aux);
}