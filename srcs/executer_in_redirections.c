/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:03:15 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/18 18:03:16 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	one_in_operator(t_fds *inputs, t_pipe_var *info, int i, int b)
{
	info->fd1 = open(inputs[i].fds, O_RDONLY);
	if (info->fd1 == -1)
	{
		info->path = NULL;
		ft_putstr_fd("Burrishell: ", 2);
		ft_putstr_fd(inputs[i].fds, 2);
		ft_putstr_fd(": No such file or directory or permission denied\n", 2);
		close(b);
		return (0);
	}
	dup2(info->fd1, STDIN_FILENO);
	close(info->fd1);
	if (inputs[i + 1].fds)
	{
		dup2(b, STDIN_FILENO);
		close(b);
	}
	return (1);
}

static void	two_in_operator(t_fds *inputs, int i, int b, char **env)
{
	char	*str;

	str = NULL;
	ft_heredoc(inputs[i].fds, env, inputs[i].expand, str);
	if (inputs[i + 1].fds)
	{
		dup2(b, STDIN_FILENO);
		close(b);
	}
}

void	make_in_redirections(t_pipe_var *info, t_fds *inputs, char **env)
{
	int	i;
	int	b;

	i = 0;
	b = -4;
	if (!inputs)
		return ;
	while (inputs[i].fds)
	{
		if (inputs[i + 1].fds)
			b = dup(STDIN_FILENO);
		if (inputs[i].is_hdoc == 0)
		{
			if (!one_in_operator(inputs, info, i, b))
				return ;
		}
		if (inputs[i].is_hdoc == 1)
			two_in_operator(inputs, i, b, env);
		i++;
	}
}
