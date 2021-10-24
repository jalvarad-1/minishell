# include "minishell.h"

static char	**add_variable(char *str, char **var)
{
	char		**tmp;
	size_t		i;
	size_t		len;

	i = 0;
	len = ft_split_len(var);
	tmp = (char **)ft_calloc(sizeof(char *), (len + 2));
	if (!tmp)
		return (0);
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
		if (locate_var(*env, str[i]) < 0)
			*env = add_variable(str[i], *env);
		i++;
	}
}
