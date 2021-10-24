#include "minishell.h"

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
int	locate_var(char **env, char *str)
{
	size_t	i;
	int		j;
	size_t	len;

	i = 0;
	while (env[i])
	{
		j = 0;
		len = 0;
		while (str[j])
		{
			if (!env[i][j])
				break ;
			if (str[j] == env[i][j])
				len++;
			j++;
		}
		if (env[i][j] == '=' && (int)len == j)
			return (i);
		i++;
	}
	return (-1);
}
/*Printea cada error que ve, pero ejecuta todo lo que puede*/
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
}
