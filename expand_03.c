#include "minishell.h"

static size_t var_len(char **env, char **var, size_t j)
{
	size_t	len;
	int		pos;
	char	*tmp;

	len = 0;
	while (var[len])
	{
		if (var[len][0] == '?')
			j += (size_t)ft_str_int_len(errno) - 2;
		else
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
		}
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

static void	get_exit_status(char *aux, size_t *j, char *var)
{
	char	*tmp;
	int		i;

	tmp = ft_itoa(errno);
	i = 0;
	while (tmp[i])
		aux[(*j)++] = tmp[i++];
	free(tmp);
	i = 1;
	while (var[i])
		aux[(*j)++] = var[i++];
}

static void	get_env_value(char *aux, char *var, char **env, size_t *j)
{
	int	pos;

	pos = locate_var(env, var);
	if (pos >= 0)
		copy_var(aux, j, env[pos]);
	else
		aux[(*j)++] = ' ' ;
}

static void	parse_init(size_t *i, size_t *j, size_t *len)
{
	*i = 0;
	*j = 0;
	*len = 0;
}

void	ft_seek_env(char **str, char **env, char **var)
{
	char	*aux;
	size_t	len;
	size_t	i;
	size_t	j;

	parse_init(&i, &j, &len);
	aux = ft_calloc(sizeof(char), var_len(env, var, ft_strlen(*str)) + 1);
	if (!aux)
		return ;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && (*str)[i + 1] && (*str)[i + 1] != '$')
		{
			if ((*str)[i + 1] == '?')
				get_exit_status(aux, &j, var[len]);
			else
				get_env_value(aux, var[len], env, &j);
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