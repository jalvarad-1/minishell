/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sons2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:03:26 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/18 18:03:29 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	aux_kamikaze_son2(t_pipe_var info, t_cmds *cmd, char ***envp)
{
	info.pid = fork();
	if (info.pid == -1)
		exit(-1);
	if (info.pid == 0)
	{
		if (g_common.ctrl_c == 1)
			exit(130);
		son_signal();
		built_in_identifier(cmd->content, envp, 0);
		execve(info.path, cmd->content, *envp);
		exit (1);
	}
}

static void	kamikaze_son2(t_pipe_var info, t_cmds *cmd, char ***envp)
{
	if (!cmd->input_fd)
		dup2(info.fd2[info.l_p][READ_END], STDIN_FILENO);
	close_unnecessary(info, -7, -7);
	if (g_common.ctrl_c == 0)
		make_in_redirections(&info, cmd->input_fd, *envp);
	if (info.fd1 == -1)
	{
		close_unnecessary(info, -8, -8);
	}
	if (g_common.ctrl_c == 0)
		make_out_redirections(&info, cmd->output_fd);
	if (info.fd1 == -1)
	{
		ft_putstr_fd("Burrishell: ", 1);
		ft_putstr_fd(": Permission denied\n", 1);
		close_unnecessary(info, -8, -8);
	}
	aux_kamikaze_son2(info, cmd, envp);
}

void	psycho_parent(t_pipe_var info, t_cmds *cmd, char ***envp)
{
	parent_signal();
	kamikaze_son2(info, cmd, envp);
	close(info.fd2[info.l_p][READ_END]);
}

void	distribute_work(t_pipe_var *info, t_cmds *aux, char ***envp, int i)
{
	if (i < info->size)
		pipe(info->fd2[i]);
	if (!is_builtin(aux->content))
	{
		if (aux->content)
			info->path = search_path(aux->content[0], *envp);
		else
			info->path = NULL;
	}
	if (aux->next && i == 0)
		kamikaze_son1(info[0], aux, envp);
	else if (aux->next && i != 0 )
		kamikaze_sonX(info[0], aux, envp);
	else if (!aux->next && info->pid != 0)
		psycho_parent(info[0], aux, envp);
}
