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

# include "minishell.h"

void	heredoc_doer(char *pre_aux)
{
	int		fd[2];

	pipe(fd);
	ft_putstr_fd(pre_aux, fd[WRITE_END]);
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
}

void	ft_heredoc(char *table, char **env, int expand)
{
	char	*str;
	char	*aux;
	char	*pre_aux;

	str = NULL;
	aux = NULL;
	pre_aux = NULL;
	if (table)
	{
		while (1)
		{
			str = readline(">");
			if (!str || !ft_strcmp(str, table))
			{
				break ;
			}
			if (!expand)
				ft_dollar_detect(&str, env, 1);
			if (!pre_aux)
			{
				pre_aux = malloc(1);
				pre_aux[0] = '\0';
			}
			aux = ft_strjoin(pre_aux, str);
			if (pre_aux)
			{
				free(pre_aux);
				pre_aux = NULL;
				free(str);
				str = NULL;
			}
			pre_aux = ft_strjoin(aux, "\n");
			free(aux);
			aux = NULL;
		}
		if (str)
		{
			free(str);
			str = NULL;
		}
		if (aux)
		{
			free(aux);
			aux = NULL;
		}
	}
	heredoc_doer(pre_aux);
	free(pre_aux);
}
