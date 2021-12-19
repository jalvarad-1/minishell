/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mod_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:02:44 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/18 18:02:46 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	move_out_quotes(char **token, int i, int *j)
{
	if (!token || !token[i])
		return ;
	if (token[i][*j] == '\'' || token[i][*j] == '"')
	{
		if (token[i][*j] == '\'')
		{
			(*j)++;
			while (token[i][*j] && token[i][*j] != '\'')
				(*j)++;
		}
		else if (token[i][*j] == '"')
		{
			(*j)++;
			while (token[i][*j] && token[i][*j] != '"')
				(*j)++;
		}
	}
}

int	mod_word_count(char const *str, char c)
{
	int	count;
	int	p;

	count = 0;
	p = 0;
	while (*str == c)
		str++;
	if (*str == '\0')
		return (0);
	while (str[p])
	{
		if (str[p] == c && str[p + 1] != c && str[p + 1] != '\0')
		{
			count++;
		}
		move_out_quotes ((char **)&str, 0, &p);
		p++;
	}
	return (count + 1);
}
