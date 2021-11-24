# include "minishell.h"

static int	check_format(char *str)
{
	int	i;
	int	len;

	i = 0;
	if (ft_isdigit(str[0]))
		return (0);
	len = 0;
	while (str[len] != '=' && str[len])
		len++;
	if (!len)
		return (0);
	while (i < len)
	{
		if (str[i] != '_' && !ft_isalnum(str[i])) //Chequear antes del '='
			return (0);
		i++;
	}
	return (1);
}

static char	**change_var_value(char **dst, char *str, int j)
{
	char	*tmp;
	char	*aux;

	if (!ft_strcmp(dst[j], str))
		return (dst);
	tmp = ft_strchr(str, '=');
	aux = cut_compare(dst[j]);
	free(dst[j]);
	dst[j] = ft_strjoin(aux, tmp);
	free(aux);
	return (dst);
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

/*Añade o cambia el valor de una variable de entorno*/
void	ft_export(char **str, char ***env, int f_or_s)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!str[i])
	{
		ft_env(*env, 0, f_or_s);
		return ;
	}
	while (str[i])
	{
		if (check_format(str[i]))
		{
			j = locate_var(*env, str[i]);
			if (j < 0)
				*env = add_variable(str[i], *env);
			else
				*env = change_var_value(*env, str[i], j);
		}
		else
			printf("Bad format\n");
		i++;
	}
	if (!f_or_s)
		exit (0);
}
