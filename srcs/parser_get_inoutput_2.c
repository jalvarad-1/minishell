/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inoutput_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:15:54 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/18 18:15:55 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remove_ops_files(char **token, char opr)
{
	char	**nw_tk;
	char	*ltt_tk;

	ltt_tk = token_in_one_str(token, opr);
	nw_tk = ft_mod_split(ltt_tk, ' ');
	free (ltt_tk);
	return (nw_tk);
}

char	*save_fd(char **token, int *i, int *j, char **env)
{
	char	*fd_name;
	int		name_size;

	name_size = 0;
	while (token[*i])
	{
		while (token[*i][*j] && token[*i][*j] == ' ')
			(*j)++;
		if (token[*i][*j] && token[*i][*j] != ' ')
			break ;
		else
			(*i)++;
	}
	name_size = fd_len(token[*i] + *j);
	ft_expand(&token[*i], env, 1);
	fd_name = ft_substr(token[*i], *j, name_size);
	return (fd_name);
}

char	*save_hdoc_end(char **token, int *i, t_fds *fds)
{
	char	*end;
	int		j;

	j = 0;
	while (token[*i][j] == '<')
		j++;
	if (ft_trim_quotes(&token[*i], 1))
		fds->expand = 1;
	else
		fds->expand = 0;
	end = ft_substr(token[*i], j, ft_strlen(token[*i]));
	fds->is_hdoc = 1;
	return (end);
}

int	redirection_counter(char **token, char opr)
{
	t_iterator	i;

	i = (t_iterator){0, 0, 0, 0};
	while (token && token[i.i])
	{
		i.j = 0;
		while (token[i.i][i.j])
		{
			move_out_quotes(token, i.i, &i.j);
			if (token[i.i][i.j] == opr)
			{
				i.b++;
				while (token[i.i][i.j] == opr)
					i.j++;
			}
			if (token[i.i][i.j])
				i.j++;
		}
		i.i++;
	}
	return (i.b);
}
