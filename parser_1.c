#include "minishell.h"

static char	*ft_conditions(char *str, size_t len)
{
	size_t	i;
	size_t	j;
	char	*aux;

	i = 0;
	j = 0;
	aux = ft_calloc(sizeof(char), len + 1);
	if (!aux)
		return (0);
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				aux[j++] = str[i++];
			i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				aux[j++] = str[i++];
			i++;
		}
		else
			aux[j++] = str[i++];
	}
	return (aux);
}

static void	ft_trim_plus(char **str, t_parse prs)
{
	char	*aux;
	size_t	len;

	len = prs.s_q + prs.d_q;
	if (!len)
		return ;
	aux = ft_conditions(*str, ft_strlen(*str) - len);
	free(*str);
	*str = ft_strdup(aux);
	free(aux);
}

static void	ft_quotes_flag(char *str, size_t *j, size_t *count, char opr)
{
	(*j)++;
	while (str[*j] != opr)
		(*j)++;
	*count += 2;
}

int	ft_trim_quotes(char **str, int out)
{
	size_t	i;
	size_t	j;
	t_parse	prs;

	i = 0;
	if (!str)
		return(0);
	while (str[i])
	{
		j = 0;
		prs = (t_parse){0, 0 ,0 ,0};
		while (str[i][j])
		{
			if (str[i][j] == '"')
				ft_quotes_flag(str[i], &j, &prs.d_q, '"');
			else if (str[i][j] == '\'')
				ft_quotes_flag(str[i], &j, &prs.s_q, '\'');
			j++;
		}
		ft_trim_plus(&str[i], prs);
		if (out)
			return (prs.s_q + prs.d_q);
		i++;
	}
	return (prs.s_q + prs.d_q);
}