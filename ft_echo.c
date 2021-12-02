/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:58:47 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/02 10:58:53 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_doer(char **str, int i, int flag)
{
	if (flag == 0)
		i = 1;
	while (str[i])
		printf("%s ", str[i++]);
	if (flag == 0)
		printf("\n");
}

static int	pass_flags(char **str, int *i, int *flag)
{
	int	j;

	j = 0;
	if (str[*i][j] == '-' && str[*i][j + 1] == 'n')
	{
		j++;
		while (str[*i][j])
		{
			if (str[*i][j] != 'n')
				break ;
			j++;
		}
		if (!str[*i][j])
			*flag = 1;
		j = 0;
		(*i)++;
		return (1);
	}
	return (0);
}

void	ft_echo(char **str, int f_or_s)
{
	int	i;
	int	flag;
	int	j;

	i = 1;
	flag = 0;
	if (!str[i])
	{
		printf("\n");
		return ;
	}
	j = 0;
	while (str[i])
	{
		if (!pass_flags(str, &i, &flag))
			break ;
	}
	echo_doer(str, i, flag);
	if (!f_or_s)
		exit (0);
}
