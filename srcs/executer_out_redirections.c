/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:06:59 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/18 18:07:03 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	one_out_operator(t_fds *outputs, t_pipe_var *info, int i)
{
	info->fd1 = open(outputs[i].fds, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (info->fd1 == -1)
	{
		info->path = NULL;
		ft_putstr_fd("Burrishell: ", 2);
		ft_putstr_fd(outputs[i].fds, 2);
		ft_putstr_fd(": No such file or directory or permission denied\n",
			 2);
		return (0);
	}
	dup2(info->fd1, STDOUT_FILENO);
	close(info->fd1);
	return (1);
}

static int	two_out_operator(t_fds *outputs, t_pipe_var *info, int i)
{
	char	buffer;

	info->fd1 = open(outputs[i].fds, O_RDWR | O_CREAT, 0644);
	if (info->fd1 == -1)
	{
		info->path = NULL;
		ft_putstr_fd("Burrishell: ", 2);
		ft_putstr_fd(outputs[i].fds, 2);
		ft_putstr_fd(": No such file or directory or permission denied\n",
			 2);
		return (0);
	}
	while (read(info->fd1, &buffer, 1))
		;
	dup2(info->fd1, STDOUT_FILENO);
	close(info->fd1);
	return (1);
}

void	make_out_redirections(t_pipe_var *info, t_fds *outputs)
{
	int	i;

	i = 0;
	if (!outputs)
		return ;
	while (outputs && outputs[i].fds)
	{
		if (outputs[i].is_hdoc == 0)
		{
			if (!one_out_operator(outputs, info, i))
				return ;
		}
		else if (outputs[i].is_hdoc == 1)
		{
			if (!two_out_operator(outputs, info, i))
				return ;
		}
		i++;
	}
}
