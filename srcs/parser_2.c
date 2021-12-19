/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:04:00 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/19 12:14:43 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	first_check(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '|'))
	{
		if (str[*i] == '|')
		{
			printf("Burrishell: parse error near `|'\n");
			return (0);
		}
		(*i)++;
	}
	return (1);
}

int	rev_vertial_bars(char *str)
{
	int	i;

	i = 0;
	if (!first_check(str, &i))
		return (0);
	while (str[i])
	{
		if (str[i] == '|')
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == '|' || !str[i])
				return ((printf("Burrishell: parse error near `|'\n") * 0));
			while (str[i] && str[i] != '|')
			{
				move_out_quotes(&str, 0, &i);
				i++;
			}
		}
		else
			i++;
	}
	return (1);
}

int	aux_op_identifier(char **str, char opr, int *i, int *j)
{
	if (str[*i][(*j) + 1] == opr)
		(*j)++;
	(*j)++;
	if (!str[*i][*j])
	{
		(*i)++;
		(*j) = 0;
	}
	if (!str[*i])
	{
		printf("Burrishell: parse error near '\\n'\n");
		return (0);
	}
	if (str[*i][*j] == '<' || str[*i][*j] == '>')
	{
		printf("Burrishell: parse error near '%c'\n", str[*i][*j]);
		return (0);
	}
	while (str[*i][*j] && str[*i][*j] != '<' && str[*i][*j] != '>')
	{
		move_out_quotes(str, *i, j);
		(*j)++;
	}
	return (1);
}

int	operator_identifier(char **str)
{
	int	i;
	int	j;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			move_out_quotes(str, i, &j);
			if (str[i][j] == '<' || str[i][j] == '>')
			{
				if (!aux_op_identifier(str, str[i][j], &i, &j))
					return (0);
			}
			else
				j++;
		}
		i++;
	}
	return (1);
}
