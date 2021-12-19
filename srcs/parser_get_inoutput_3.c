/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inoutput_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:16:00 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/18 18:16:02 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fd_len(char *token)
{
	int	len;

	len = 0;
	while (token[len] && token[len] != '<' && token[len] != '>')
	{
		if (token[len] == '"')
		{
			len++;
			while (token[len] != '"' && token[len])
				len++;
		}
		else if (token[len] == '\'')
		{
			len++;
			while (token[len] != '\'' && token[len])
				len++;
		}
		len++;
	}
	return (len);
}

void	mod_move_out_quotes(char *token, int *i)
{
	if (!token || !token[*i])
		return ;
	if (token[*i] == '\'' || token[*i] == '"')
	{
		if (token[*i] == '\'')
		{
			token[(*i)++] = ' ';
			while (token[*i] && token[*i] != '\'')
				token[(*i)++] = ' ';
		}
		else if (token[*i] == '"')
		{
			token[(*i)++] = ' ';
			while (token[*i] && token[*i] != '"')
				token[(*i)++] = ' ';
		}
	}
}
