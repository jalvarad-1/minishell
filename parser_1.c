#include "minishell.h"

/*static char	*ft_conditions(char **str, size_t len)
{
	size_t	i;
	size_t	j;
	char	*aux;
	size_t	actual_len;

	i = 0;
	j = 0;
	actual_len = ft_strlen(*str) - len;
	aux = ft_calloc(sizeof(char), actual_len + 2);
	if (!aux)
		return (0);
	while (j < actual_len)
	{
		if ((*str)[i] == '\\')
		{
			if ((*str)[i + 1])
				aux[j++] = (*str)[++i];
		}
		else if ((*str)[i] != '"' && (*str)[i] != '\'')
			aux[j++] = (*str)[i];
		i++;
	}
	return (aux);
}

static	void	ft_trim_plus(char **str, t_parse prs)
{
	char	*aux;
	size_t	len;

	len = prs.s_q + prs.d_q;
	aux = ft_conditions(str, len);
	free(*str);
	*str = ft_strdup(aux);
	free(aux);
}*/

static void	ft_dollar_expand(char **str, char **env, t_parse prs)
{
	char	**aux;
	size_t	i;
	size_t	j;

	aux = ft_calloc(sizeof(char*), prs.n_dollar + 1);
	if (!aux)
		return ;
	i = 0;
	j = 0;
	while (i < prs.n_dollar)
	{
		while ((*str)[prs.pos_dollar[i] + j] != ' ' && *(str))
			j++;
		aux[i] = ft_substr(*str, prs.pos_dollar[i], j);
		i++;
	}
//	i = 0;
//	while (aux[i])
//	{
//		printf("%s\n", aux[i]);
//		i++;
//	}
	free_matrix(aux);
}

/*0 si está todo ok
1 si da error*/
/*Hay que distinguir entre comillas simples y dobles*/
/*Backslash precede un caracter especial para printearlo
EJ = // el primero hace posible que se imprima el segundo
EJ 2 = /" Hace que se imprima la comilla y por tanto
no cuenta para el contador de comillas cerradas*/
static size_t	*get_pos_dollar(size_t j, t_parse prs, size_t **pos)
{
	size_t	*aux;
	size_t	i;

	i = 0;
	aux = malloc(sizeof(size_t) * prs.n_dollar);
	while (i < prs.n_dollar - 1)
	{
		aux[i] = (*pos)[i];
		i++;
	}
	aux[i] = j;
	if (*pos)
		free(*pos);
	return (aux);
}

int	ft_parser(char **str, char **env)
{
	t_parse	prs;
	size_t	i;

	prs = (t_parse){0, 0, 0, 0};
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '"')
			prs.d_q++;
		else if ((*str)[i] == '\'')
			prs.s_q++;
		else if ((*str)[i] == '$')
		{
			prs.n_dollar++;
			prs.pos_dollar = get_pos_dollar(i, prs, &prs.pos_dollar);
		}
		i++;
	}
	if (prs.s_q % 2 || prs.d_q % 2)
	{
		printf("Error, unclosed quotation marks\n");
		return (1);
	}
	i = 0;
//	while (i < prs.n_dollar)
//		printf("%zu\n", prs.pos_dollar[i++]);
	if (prs.n_dollar)
	{
		ft_dollar_expand(str, env, prs);
		free(prs.pos_dollar);
	}
	return (0);
}

/*3.1.2.1 Escape Character
A non-quoted backslash ‘\’ is the Bash escape character.
It preserves the literal value of the next character that follows,
with the exception of newline. If a \newline pair appears,
and the backslash itself is not quoted, the \newline is treated as a line continuation
(that is, it is removed from the input stream and effectively ignored).

Next: Double Quotes, Previous: Escape Character, Up: Quoting   [Contents][Index]

3.1.2.2 Single Quotes
Enclosing characters in single quotes (‘'’)
preserves the literal value of each character within the quotes.
A single quote may not occur between single quotes, even when preceded by a backslash.

Next: ANSI-C Quoting, Previous: Single Quotes, Up: Quoting   [Contents][Index]

3.1.2.3 Double Quotes
Enclosing characters in double quotes (‘"’)
preserves the literal value of all characters within the quotes,
with the exception of ‘$’, ‘`’, ‘\’, and, when history expansion is enabled, ‘!’.
When the shell is in POSIX mode (see Bash POSIX Mode),
the ‘!’ has no special meaning within double quotes, even when history expansion is enabled.
The characters ‘$’ and ‘`’ retain their special meaning within double quotes (see Shell Expansions).
The backslash retains its special meaning only when followed by
one of the following characters: ‘$’, ‘`’, ‘"’, ‘\’, or newline. Within double quotes,
backslashes that are followed by one of these characters are removed.
Backslashes preceding characters without a special meaning are left unmodified.
A double quote may be quoted within double quotes by preceding it with a backslash.
If enabled, history expansion will be performed unless an ‘!’ appearing in double quotes
is escaped using a backslash. The backslash preceding the ‘!’ is not removed.

The special parameters ‘*’ and ‘@’ have special meaning when in double quotes
(see Shell Parameter Expansion).*/
