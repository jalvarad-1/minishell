/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 12:37:21 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/12 12:37:24 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_double_quotes(char **str, size_t *i, size_t *j, t_parse *prs)
{
	(*j)++;
	while (str[*i][*j] != '"')
	{
		if (str[*i][*j] == '$' && str[*i][(*j) + 1] && str[*i][(*j) + 1] != '"')
		{
			prs->n_dollar++;
			prs->pos_dollar = get_pos_dollar((*j) + 1, prs, &prs->pos_dollar);
		}
		(*j)++;
	}
}

static void	ft_single_quotes(char **str, size_t *i, size_t *j)
{
	(*j)++;
	while (str[*i][*j] != '\'')
		(*j)++;
}

static void	ft_has_dollar(t_parse *prs, size_t j)
{
	prs->n_dollar++;
	prs->pos_dollar = get_pos_dollar(j + 1, prs, &prs->pos_dollar);
}

static void	ft_expander(char **str, char **env, t_parse *prs)
{
	if (prs->n_dollar)
	{
		ft_dollar_expand(str, env, *prs);
		free(prs->pos_dollar);
	}
	prs->n_dollar = 0;
	prs->pos_dollar = NULL;
}

void	ft_dollar_detect(char **str, char **env, int flag)
{
	t_parse	prs;

	prs = (t_parse){0, 0, 0, 0};
	if (!str)
		return ;
	while (str[prs.s_q])
	{
		prs.d_q = 0;
		while (str[prs.s_q][prs.d_q])
		{
			if (str[prs.s_q][prs.d_q] == '"')
				ft_double_quotes(str, &prs.s_q, &prs.d_q, &prs);
			else if (str[prs.s_q][prs.d_q] == '\'')
				ft_single_quotes(str, &prs.s_q, &prs.d_q);
			else if (str[prs.s_q][prs.d_q] == '$'
				&& str[prs.s_q][prs.d_q + 1]
				&& str[prs.s_q][prs.d_q + 1] != '$')
				ft_has_dollar(&prs, prs.d_q);
			prs.d_q++;
		}
		ft_expander(&str[prs.s_q], env, &prs);
		if (flag)
			return ;
		prs.s_q++;
	}
}
