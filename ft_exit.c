/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:43:02 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/02 10:43:07 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str_is_numeric(char *str)
{
	int	a;
	int	b;

	a = 0;
	b = 1;
	while (str[a] != '\0')
	{
		while (str[a] == ' ')
			a++;
		if (str[a] == '+' || str[a] == '-' )
			a++;
		while (str[a] >= '0' && str[a] <= '9')
		{
			a++;
			b = b * 1;
		}
		while (str[a] == ' ')
			a++;
		if (str[a] != 0)
			return (0);
		return (b);
	}
	return (b);
}

void	ft_exit(char **str)
{
	int	argc;
	int	i;

	argc = 0;
	i = 0;
	printf("exit\n");
	while (str[argc])
		argc++;
	if (argc >= 2)
	{
		if (argc > 2 && ft_str_is_numeric(str[1]))
		{
			printf("minishell: exit: too many arguments\n");
			i = ft_atoi(str[1]) % 255;
		}
		else if (!ft_str_is_numeric(str[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n", str[1]);
			i = 255;
		}
		else
			i = ft_atoi(str[1]) % 255;
	}
	exit(i);
}
