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
	char	**split;
	int		i;

	str = NULL;
	aux = NULL;
	pre_aux = NULL;
	split = NULL;
	if (table)
	{
		while (1)
		{
			str = readline(">");
			if (!str || !ft_strcmp(str, table))
				break ;
			aux = ft_strjoin(pre_aux, str);
			if (pre_aux)
			{
				free(pre_aux);
				pre_aux = NULL;
				free(str);
				str = NULL;
			}
			pre_aux = ft_strjoin(aux, "\n");
		}
		printf("salgo\n");
		if (str)
			free(str);
		if (aux)
			free(aux);
		if (pre_aux)
		{
			split = ft_mod_split(pre_aux, '\n');
			if (!expand)
				ft_expand(split, env, 0);
			if (pre_aux)
				free(pre_aux);
			i = 0;
			aux = NULL;
			pre_aux = NULL;
			while (split[i])
			{
				aux = ft_strjoin(pre_aux, split[i]);
				if (pre_aux)
				{
						free(pre_aux);
						pre_aux = NULL;
				}
				pre_aux = ft_strjoin(aux, "\n");
				i++;
			}
		}
	}
	heredoc_doer(pre_aux);
	free(pre_aux);
}
