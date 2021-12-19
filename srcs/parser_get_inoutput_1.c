/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inoutput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:15:24 by jalvarad          #+#    #+#             */
/*   Updated: 2021/12/15 16:15:25 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	aux_token_in_one_str(char *ltt_tk, char optr)
{
	int	i;

	i = 0;
	while (ltt_tk[i])
	{
		move_out_quotes(&ltt_tk, 0, &i);
		if (ltt_tk[i] == optr)
		{
			while (ltt_tk[i] == optr)
			{
				ltt_tk[i] = ' ';
				i++;
			}
			while (ltt_tk[i] && ltt_tk[i] == ' ')
				i++;
			while (ltt_tk[i] && ltt_tk[i] != ' ')
			{
				mod_move_out_quotes(ltt_tk, &i);
				ltt_tk[i++] = ' ';
			}
		}
		i++;
	}
}

char	*token_in_one_str(char **token, char optr)
{
	char	*ltt_tk;
	char	*aux;
	int		i;

	i = 0;
	ltt_tk = ft_strjoin(token[i], " ");
	while (token[++i])
	{
		aux = ft_strjoin(ltt_tk, token[i]);
		free(ltt_tk);
		ltt_tk = ft_strjoin(aux, " ");
		free(aux);
	}
	aux_token_in_one_str(ltt_tk, optr);
	return (ltt_tk);
}

static void	found_opr_case(char **token, char **env, t_fds *fds, t_iterator *i)
{
	if (token[i->i][++i->j])
	{
		if (token[i->i][i->j] == i->opr)
		{
			i->j++;
			if (!token[i->i][i->j])
			{
				i->i++;
				i->j = 0;
			}
			if (i->opr == '<')
				fds[i->b].fds = save_hdoc_end(token, &i->i, &fds[i->b]);
			else if (i->opr == '>')
				fds[i->b] = (t_fds){save_fd(token, &i->i, &i->j, env), 1, 0};
		}
		else
			fds[i->b] = (t_fds){save_fd(token, &i->i, &i->j, env), 0, 0};
	}
	else
	{
		i->i++;
		i->j = 0;
		fds[i->b] = (t_fds){save_fd(token, &i->i, &i->j, env), 0, 0};
	}
}

static void	aux_get_inputs(char **token, char opr, char **env, t_fds *fds)
{
	t_iterator	i;

	i = (t_iterator){0, 0, 0, opr};
	while (token[i.i])
	{
		i.j = 0;
		move_out_quotes(token, i.i, &i.j);
		while (token[i.i][i.j])
		{
			if (token[i.i][i.j] == opr)
			{
				found_opr_case(token, env, fds, &i);
				i.b++;
			}
			i.j++;
		}
		i.i++;
	}
	fds[i.b].fds = NULL;
}

t_fds	*ft_get_inputs(char ***token, char opr, char **env)
{
	char	**new_token;
	t_fds	*fds;
	int		i;

	i = redirection_counter(*token, opr);
	if (!i)
		return (NULL);
	fds = malloc(sizeof(t_fds) * (i + 1));
	if (!fds)
		return (NULL);
	aux_get_inputs(token[0], opr, env, fds);
	new_token = remove_ops_files(*token, opr);
	free_matrix(*token);
	*token = new_token;
	return (fds);
}
