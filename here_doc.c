/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:30:43 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/02 12:30:45 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_str(char **str)
{
	free(*str);
	*str = NULL;
}

static void	heredoc_doer(char *pre_aux)
{
	int		fd[2];

	pipe(fd);
	ft_putstr_fd(pre_aux, fd[WRITE_END]);
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
}

static void	ft_prepare_str(char *str, char **pre_aux)
{
	char	*aux;

	aux = NULL;
	aux = ft_strjoin(*pre_aux, str);
	if (*pre_aux)
	{
		del_str(pre_aux);
		del_str(&str);
	}
	*pre_aux = ft_strjoin(aux, "\n");
	del_str(&aux);
	if (aux)
		del_str(&aux);
}

void	ft_heredoc(char *table, char **env, int expand)
{
	char	*str;
	char	*pre_aux;

	str = NULL;
	pre_aux = NULL;
	if (table)
	{
		while (1)
		{
			str = readline(">");
			if (!str || !ft_strcmp(str, table))
				break ;
			if (!expand)
				ft_dollar_detect(&str, env, 1);
			if (!pre_aux)
				pre_aux = ft_calloc(1, 1);
			ft_prepare_str(str, &pre_aux);
		}
	}
	heredoc_doer(pre_aux);
	free(pre_aux); // Esto es muy raro que de un doble free
	free(str);
}
