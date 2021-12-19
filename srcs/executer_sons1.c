/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sons1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:03:34 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/18 18:03:35 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	only_son(t_pipe_var info, t_cmds *cmd, char ***envp)
{
	make_in_redirections(&info, cmd->input_fd, *envp);
	if (info.fd1 == -1)
		close_unnecessary(info, -8, -8);
	if (g_common.ctrl_c == 0)
		make_out_redirections(&info, cmd->output_fd);
	if (info.fd1 == -1)
		close_unnecessary(info, -8, -8);
	info.pid = fork();
	if (info.pid == -1)
		exit(-1);
	if (info.pid == 0)
	{
		if (g_common.ctrl_c == 1)
			exit(130);
		son_signal();
		execve(info.path, cmd->content, *envp);
		exit (127);
	}
}

static void	aux_kamikaze_son1(t_pipe_var info, t_cmds *cmd, char ***envp)
{
	info.pid = fork();
	if (info.pid == -1)
		exit(-1);
	if (info.pid == 0)
	{
		if (g_common.ctrl_c == 1)
			exit(130);
		son_signal();
		close(info.fd2[0][READ_END]);
		built_in_identifier(cmd->content, envp, 0);
		execve(info.path, cmd->content, *envp);
		exit (127);
	}
}

void	kamikaze_son1(t_pipe_var info, t_cmds *cmd, char ***envp)
{
	make_in_redirections(&info, cmd->input_fd, *envp);
	if (info.fd1 == -1)
	{
		close_unnecessary(info, -8, -8);
	}
	dup2(info.fd2[0][WRITE_END], STDOUT_FILENO);
	close(info.fd2[0][WRITE_END]);
	if (g_common.ctrl_c == 0)
		make_out_redirections(&info, cmd->output_fd);
	if (info.fd1 == -1)
	{
		close_unnecessary(info, -8, -8);
	}
	close_unnecessary(info, info.fd2[0][READ_END], info.fd2[0][WRITE_END]);
	aux_kamikaze_son1(info, cmd, envp);
}

static void	aux_kamikaze_sonX(t_pipe_var info, t_cmds *cmd, char ***envp)
{
	info.pid = fork();
	if (info.pid == -1)
		exit(-1);
	if (info.pid == 0)
	{
		if (g_common.ctrl_c == 1)
			exit(130);
		son_signal();
		close_unnecessary(info, info.fd2[info.l_p][READ_END],
			info.fd2[info.n_p][WRITE_END]);
		built_in_identifier(cmd->content, envp, 0);
		execve(info.path, cmd->content, *envp);
		exit (1);
	}
}

void	kamikaze_sonX(t_pipe_var info, t_cmds *cmd, char ***envp)
{
	if (!cmd->input_fd)
		dup2(info.fd2[info.l_p][READ_END], STDIN_FILENO);
	close(info.fd2[info.l_p][READ_END]);
	if (g_common.ctrl_c == 0)
		make_in_redirections(&info, cmd->input_fd, *envp);
	if (info.fd1 == -1 )
	{
		close_unnecessary(info, -8, -8);
	}
	dup2(info.fd2[info.n_p][WRITE_END], STDOUT_FILENO);
	close(info.fd2[info.n_p][WRITE_END]);
	if (g_common.ctrl_c == 0)
		make_out_redirections(&info, cmd->output_fd);
	if (info.fd1 == -1)
	{
		close_unnecessary(info, -8, -8);
	}
	aux_kamikaze_sonX(info, cmd, envp);
}
