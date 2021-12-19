/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:03:48 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/18 18:03:50 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**create_doble_array(t_cmds *cmd)
{
	int		**pipe_array;
	int		i;
	int		b;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	pipe_array = (int **)malloc(sizeof(int *) * (i - 1));
	b = i - 1;
	i = 0;
	while (i < b)
	{
		pipe_array[i] = malloc(sizeof(int) * 2);
		pipe_array[i][0] = -4;
		pipe_array[i][1] = -4;
		i++;
	}
	return (pipe_array);
}

void	init_pipe_vars(t_pipe_var *info, t_cmds *cmd)
{
	info->size = ft_lstsize(cmd) - 1;
	info->fd2 = create_doble_array(cmd);
	info->pid = 1;
	info->path = NULL;
	info->fd1 = -42;
}

void	free_ptrs_and_wait(t_pipe_var *info, int i)
{
	int	d;

	d = 0;
	if (info->fd2 != NULL)
	{
		while (d < i - 1)
			free(info->fd2[d++]);
		free(info->fd2);
	}
	while (info->pid != 0 && i > 0)
	{
		wait(&g_common.exit_status);
		if (WIFSIGNALED(g_common.exit_status) == TRUE)
			g_common.exit_status += 128;
		else
			g_common.exit_status = WEXITSTATUS(g_common.exit_status);
		i--;
	}
	if (info->path)
		free(info->path);
	g_common.pid = 0;
}

void	aux_pipex(t_pipe_var *info, int b, int c, int i)
{
	if (info->path != NULL)
	{
		free(info->path);
		info->path = NULL;
	}
	if (i < info->size)
	{
		close(info->fd2[i][WRITE_END]);
		if (i > 0)
			close(info->fd2[info->l_p][READ_END]);
	}
	dup2(b, STDIN_FILENO);
	close(b);
	dup2(c, STDOUT_FILENO);
	close(c);
}

void	pipex(char ***envp, t_cmds *cmd)
{
	t_pipe_var	info;
	t_cmds		*aux;
	int			i;
	int			b;
	int			c;

	init_pipe_vars(&info, cmd);
	aux = cmd;
	i = 0;
	if (aux && !info.size)
	{
		i = if_one_cmd(aux, &info, envp);
	}
	while (aux && info.size > 0)
	{
		b = dup(STDIN_FILENO);
		c = dup(STDOUT_FILENO);
		distribute_work(&info, aux, envp, i);
		aux_pipex(&info, b, c, i);
		aux = aux->next;
		info.l_p = i;
		i++;
		info.n_p = i;
	}
	free_ptrs_and_wait(&info, i);
}
