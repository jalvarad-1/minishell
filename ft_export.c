# include "minishell.h"

static char	*change_var_value(char *dst, char *str)
{
	if (!ft_strcmp(dst, str))
		return (dst);
	
	return(dst);
}

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

/*Debe ser capaz de cambiar el valor de las variables ya asignadas*/
/*El formato es variable=algo. variable= es igual a ""*/
/*Si lleva comillas se pega tal cual. Si no, se añaden*/
void	ft_export(char **str, char ***env)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!str[i])
	{
		ft_env(*env, 0);
		return ;
	}
	while (str[i])
	{
		j = locate_var(*env, str[i]);
//		printf("%d\n", j);
		if (j < 0)
			*env = add_variable(str[i], *env);
		else
			*env[i] = change_var_value(*env[i], str[i]);
		i++;
	}
}
