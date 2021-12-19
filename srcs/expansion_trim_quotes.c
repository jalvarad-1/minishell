/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 12:41:10 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/12 12:41:12 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_without_quotes(char *dst, char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '"')
		{
			i++;
			while (src[i] != '"')
				dst[j++] = src[i++];
			i++;
		}
		else if (src[i] == '\'')
		{
			i++;
			while (src[i] != '\'')
				dst[j++] = src[i++];
			i++;
		}
		else
			dst[j++] = src[i++];
	}
}

static char	*ft_conditions(char *str, size_t len)
{
	char	*aux;

	aux = ft_calloc(sizeof(char), len + 1);
	if (!aux)
		return (0);
	copy_without_quotes(aux, str);
	return (aux);
}

static void	ft_trim_plus(char **str, t_parse prs)
{
	char	*aux;
	size_t	len;

	len = prs.s_q + prs.d_q;
	if (!len)
		return ;
	aux = ft_conditions(*str, ft_strlen(*str) - len);
	free(*str);
	*str = ft_strdup(aux);
	free(aux);
}

static void	ft_quotes_flag(char *str, int *j, size_t *count, char opr)
{
	(*j)++;
	while (str[*j] != opr)
		(*j)++;
	*count += 2;
}

int	ft_trim_quotes(char **str, int out)
{
	t_iterator	i;
	t_parse		prs;

	i = (t_iterator){0, 0, 0, 0};
	if (!str)
		return (0);
	while (str[i.i])
	{
		i.j = 0;
		prs = (t_parse){0, 0, 0, 0};
		while (str[i.i][i.j])
		{
			if (str[i.i][i.j] == '"')
				ft_quotes_flag(str[i.i], &i.j, &prs.d_q, '"');
			else if (str[i.i][i.j] == '\'')
				ft_quotes_flag(str[i.i], &i.j, &prs.s_q, '\'');
			i.j++;
		}
		ft_trim_plus(&str[i.i], prs);
		if (out)
			return (prs.s_q + prs.d_q);
		i.i++;
	}
	return (prs.s_q + prs.d_q);
}
