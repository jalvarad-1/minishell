#include "minishell.h"

static char	*ft_conditions(char *str, size_t len)
{
	size_t	i;
	size_t	j;
	char	*aux;
	size_t	actual_len;

	i = 0;
	j = 0;
	actual_len = ft_strlen(str) - len;
	aux = ft_calloc(sizeof(char), actual_len + 2);
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
void	ft_trim_plus(char **str, t_parse prs)
{
	char	*aux;
	size_t	len;

	len = prs.s_q + prs.d_q;
	aux = ft_conditions(*str, len);
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
		if ((*str)[i] == '$' && (*str)[i + 1] && (*str)[i + 1] != '$')
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
				&& (*str)[prs.pos_dollar[i] + j] != '$' && (*str)[prs.pos_dollar[i] + j] != '"'
				&& (*str)[prs.pos_dollar[i] + j] != '\'')
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

// $$ Da EL PID DE BASH. Podriamos o ignorarlo o coger el PID de la minishell
void	ft_dollar_detect(char **str, char **env)
{
	size_t	i;
	size_t	j;
	t_parse	prs;

	i = 0;
	prs = (t_parse){0, 0, 0, 0};
	if (!str)
		return ;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '"')
			{
				j++;
				while (str[i][j] != '"')
				{
					if (str[i][j] == '$' && str[i][j + 1] && str[i][j + 1] != '"')
					{
						prs.n_dollar++;
						prs.pos_dollar = get_pos_dollar(j + 1, prs, &prs.pos_dollar);
					}
					j++;
				}
			}
			else if (str[i][j] == '\'')
			{
				j++;
				while (str[i][j] != '\'')
					j++;
			}
			else if (str[i][j] == '$' && str[i][j + 1] && str[i][j + 1] != '$')
			{
				prs.n_dollar++;
				prs.pos_dollar = get_pos_dollar(j + 1, prs, &prs.pos_dollar);
			}
			j++;
		}
		if (prs.n_dollar)
		{
			ft_dollar_expand(&str[i], env, prs);
			free(prs.pos_dollar);
		}
		prs.n_dollar = 0;
		i++;
	}
}
