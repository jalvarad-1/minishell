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

void	del_str(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void	ft_wait_heredoc(int *fd, char **pre_aux)
{
	int	status;

	status = 0;
	wait(&status);
	if (status != 0)
		g_common.ctrl_c = 1;
	del_str(pre_aux);
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
}

void	ft_heredoc_aux3(char **str, char **aux, int *fd, char *pre_aux)
{
	del_str(str);
	del_str(aux);
	close(fd[READ_END]);
	ft_putstr_fd(pre_aux, fd[WRITE_END]);
	close(fd[WRITE_END]);
	exit(0);
}

void	ft_heredoc_aux2(char **aux, char **pre_aux, char **str)
{
	*aux = ft_strjoin(*pre_aux, *str);
	del_str(pre_aux);
	del_str(str);
	*pre_aux = ft_strjoin(*aux, "\n");
	del_str(aux);
}

void	ft_heredoc(char *table, char **env, int expand, char *str)
{
	char	*aux;
	char	*pre_aux;
	int		fd[2];
	int		status;

	aux = NULL;
	pre_aux = ft_calloc(1, 1);
	pipe(fd);
	status = fork();
	if (table && status == 0)
	{
		son_signal();
		while (1)
		{
			str = readline(">");
			if (!str || !ft_strcmp(str, table))
				break ;
			if (!expand)
				ft_dollar_detect(&str, env, 1);
			ft_heredoc_aux2(&aux, &pre_aux, &str);
		}
		ft_heredoc_aux3(&str, &aux, fd, pre_aux);
	}
	ft_wait_heredoc(fd, &pre_aux);
}
