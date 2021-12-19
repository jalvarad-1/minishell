/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 12:35:44 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/19 13:16:07 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_exit_status(char *aux, size_t *j, char *var)
{
	char	*tmp;
	int		i;

	tmp = ft_itoa(g_common.exit_status);
	i = 0;
	while (tmp[i])
		aux[(*j)++] = tmp[i++];
	free(tmp);
	i = 1;
	while (var[i])
		aux[(*j)++] = var[i++];
}

static void	copy_var(char *aux, size_t *j, char *env)
{
	char	*tmp;
	size_t	i;

	i = 1;
	tmp = ft_strchr(env, '=');
	if (!tmp)
	{
		aux[*j] = ' ';
		*j += 1;
		return ;
	}
	while (tmp[i])
	{
		aux[*j] = tmp[i];
		*j += 1;
		i++;
	}
}

void	get_env_value(char *aux, char *var, char **env, size_t *j)
{
	int	pos;

	pos = locate_var(env, var);
	if (pos >= 0)
		copy_var(aux, j, env[pos]);
	else
		aux[(*j)++] = ' ' ;
}

size_t	*get_pos_dollar(size_t j, t_parse *prs, size_t **pos)
{
	size_t	*aux;
	size_t	i;

	i = 0;
	aux = malloc(sizeof(size_t) * prs->n_dollar);
	if (!aux)
		return (0);
	while (i < prs->n_dollar - 1)
	{
		aux[i] = (*pos)[i];
		i++;
	}
	aux[i] = j;
	if (prs->pos_dollar)
		free(prs->pos_dollar);
	return (aux);
}

void	ft_dollar_expand(char **str, char **env, t_parse prs)
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
		while (((*str)[prs.pos_dollar[i] + j]
			&& (*str)[prs.pos_dollar[i] + j] != ' ')
			&& (*str)[prs.pos_dollar[i] + j] != '$'
			&& (*str)[prs.pos_dollar[i] + j] != '"'
			&& (*str)[prs.pos_dollar[i] + j] != '\'')
			j++;
		aux[i] = ft_substr(*str, prs.pos_dollar[i], j);
		i++;
	}
	ft_seek_env(str, env, aux);
	free_matrix(aux);
}
