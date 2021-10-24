# include "minishell.h"

/*Hacer funcion realloc seria la ostia, todo por no usar listas THX JOSE*/
static char	**add_variable(char *str, char **var)
{
	char		**tmp;
	size_t		len;
	size_t		i;

	len = ft_split_len(var);
	tmp = (char **)ft_calloc(sizeof(char *), (len + 1));
	if (!tmp)
		return (0);
	i = 0;
	while (i < len)
	{
		tmp[i] = ft_strdup(var[i]);
		free(var[i]);
		i++;
	}
	tmp[i] = ft_strdup(str);
	free(var);
	return (tmp);
}

/*Export sin argumentos muestra la lista de TODAS LAS VARIABLES
asignadas y no asignadas.*/
void	ft_export(char **str, char ***env)
{
	int	i;

	i = 1;
	if (!str[i])
	{
		ft_env(*env, 0);
		return ;
	}
	while (str[i])
	{
		*env = add_variable(str[i], *env);
		i++;
	}
}
