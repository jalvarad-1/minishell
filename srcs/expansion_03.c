/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:14:48 by jalvarad          #+#    #+#             */
/*   Updated: 2021/12/19 13:14:36 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand(char **token, char **env, int flag)
{
	ft_dollar_detect(token, env, flag);
	ft_trim_quotes(token, flag);
}

static size_t	var_len(char **env, char **var, size_t j)
{
	size_t	len;
	int		pos;
	char	*tmp;

	len = 0;
	while (var[len])
	{
		if (var[len][0] == '?')
			j += (size_t)ft_str_int_len(g_common.exit_status) - 2;
		else
		{
			pos = locate_var(env, var[len]);
			if (pos >= 0)
			{
				tmp = ft_strchr(env[pos], '=');
				if (!tmp)
					j+=1;
				else
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

static void	parse_init(size_t *i, size_t *j, size_t *len)
{
	*i = 0;
	*j = 0;
	*len = 0;
}

static void	final_string(char **str, char *aux)
{
	free(*str);
	*str = ft_strtrim(aux, " ");
	free(aux);
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
			i += ft_strlen(var[len++]);
		}
		else
			aux[j++] = (*str)[i];
		i++;
	}
	final_string(str, aux);
}
