#include "minishell.h"

static char	*ft_conditions(char **str, size_t len)
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
void	ft_trim_plus(char **str, t_parse prs)
{
	char	*aux;
	size_t	len;

	len = prs.s_q + prs.d_q;
	aux = ft_conditions(str, len);
	free(*str);
	*str = ft_strdup(aux);
	free(aux);
}

/*Busca el valor de la variable en env y saca la longitud*/
static size_t var_len(char **env, char **var, size_t j)
{
	size_t	len;
	int		pos;
	char	*tmp;

	len = 0;
	while (var[len])
	{
		pos = locate_var(env, var[len]);
		if (pos >= 0)
		{
			tmp = ft_strchr(env[pos], '=');
			j += ft_strlen(tmp + 1);
		}
		else
			j++;
		j -= ft_strlen(var[len]);
		len++;
	}
	return (j);
}

static void	copy_var(char *aux, size_t *j, char *env)
{
	char	*tmp;
	size_t	i;

	i = 1;
	tmp = ft_strchr(env, '=');
	while (tmp[i])
	{
		aux[*j] = tmp[i];
		*j +=1;
		i++;
	}
}

/*Devuelve la cadena, ahora sí, con la variable que toca en env
Si no la encuentra deja un espacio*/
/*Para guardar memoria adecuadamente :
	Coger la longitud de la cadena entera, sumar la longitud del valor de la variable*/

/* TODO $? Debe expandirse al estado de salida del último comando*/
static void	ft_seek_n_destroy(char **str, char **env, char **var)
{
	char	*aux;
	int		pos;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len = 0;
	aux = ft_calloc(sizeof(char), var_len(env, var, ft_strlen(*str)) + 1);
	if (!aux)
		return ;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			pos = locate_var(env, var[len]);
			if (pos >= 0)
				copy_var(aux, &j, env[pos]);
			else
				aux[j++] = ' ';
			i+= ft_strlen(var[len++]);
		}
		else
			aux[j++] = (*str)[i];
		i++;
	}
	free(*str);
	*str = ft_strtrim(aux, " ");
	free(aux);
}

/*echo $USER pepe $PACO $OLDPWD $PWD*/
static void	ft_dollar_expand(char **str, char **env, t_parse prs)
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
				&& (*str)[prs.pos_dollar[i] + j] != '$' && (*str)[prs.pos_dollar[i] + j] != '"')
			j++;
		aux[i] = ft_substr(*str, prs.pos_dollar[i], j);
		i++;
	}
	ft_seek_n_destroy(str, env, aux);
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
	if (!aux)
		return (0);
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

void	ft_dollar_detect(char **str, char **env)
{
	size_t	i;
	size_t	j;
	t_parse	prs;

	i = 0;
	prs = (t_parse){0, 0, 0, 0};
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '$')
			{
				prs.n_dollar++;
				prs.pos_dollar = get_pos_dollar(j + 1, prs, &prs.pos_dollar);
			}
			j++;
		}
		if (prs.n_dollar)
			ft_dollar_expand(&str[i], env, prs);
		i++;
	}
	if (prs.n_dollar)
		free(prs.pos_dollar);
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
