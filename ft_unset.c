#include "minishell.h"

/*Hace una especide de realloc a lo guarro. En esencia elimina la cadena anterior
para copiarse en la nueva, excepto la variable que no deseamos en pos*/
static char	**destroy_var(char **var, int pos)
{
	char		**tmp;
	size_t		i;
	size_t		j;
	size_t		len;

	i = 0;
	j = 0;
	len = ft_split_len(var);
	tmp = (char **)ft_calloc(sizeof(char *), (len));
	if (!tmp)
		return (0);
	while (i < len)
	{
		if ((int)i != pos)
		{
			tmp[j] = ft_strdup(var[i]);
			j++;
		}
		free(var[i]);
		i++;
	}
	free(var);
	return (tmp);
}

/*Devuelve la posicion de la variable a eliminar si la encuentra.
	En caso de no encontrarla devuelve -1*/
/*STRNSTR O STRNCMP deberian funcionar para comprarar la cadena hasta encontrar el '=' Hay que encontrar la cadena exacta hasta el igual*/
char *cut_compare(char *str)
{
	char	*aux;
	size_t 	len;

	len = 0;
	while (str[len] != '=' && str[len])
		len++;
	aux = ft_calloc(sizeof(char), len);
	ft_strncpy(aux, str, len);
	return (aux);
}

int	locate_var(char **env, char *str)
{
	char	*aux;
	char	*tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		aux = cut_compare(env[i]);
		tmp = cut_compare(str);
		if (!ft_strcmp(aux, tmp))
		{
			free(aux);
			free(tmp);
			return (i);
		}
		free(aux);
		free(tmp);
		i++;
	}
	return (-1);
}
/*Printea cada error que ve, pero ejecuta todo lo que puede*/

/*Una variable de entorno puede empezar por letra o '_' y contener caracteres alfanumericos*/
void	ft_unset(char **str, char ***env)
{
	size_t		i;
	int			j;

	i = 1;
	j = -1;
	if (!str[i])
		return ;
	while (str[i])
	{
		if (!ft_strchr(str[i], '='))
			j = locate_var(*env, str[i]);
		else
			printf("unset : %s: invalid parameter\n", str[i]);
		if (j >= 0)
			*env = destroy_var(*env, j);
		i++;
	}
	exit (0);
}
