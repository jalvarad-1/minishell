/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:06:29 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/18 18:06:31 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	if_is_one_builtin_cmd(t_cmds *aux, t_pipe_var *info, char ***envp)
{
	info->aux_fds[READ_END] = dup(STDIN_FILENO);
	make_in_redirections(info, aux->input_fd, *envp);
	info->aux_fds[WRITE_END] = dup(STDOUT_FILENO);
	if (g_common.ctrl_c == 0)
		make_out_redirections(info, aux->output_fd);
	if (info->fd1 != -1 && g_common.ctrl_c == 0)
		built_in_identifier(aux->content, envp, 1);
	dup2(info->aux_fds[READ_END], STDIN_FILENO);
	close(info->aux_fds[READ_END]);
	dup2(info->aux_fds[WRITE_END], STDOUT_FILENO);
	close(info->aux_fds[WRITE_END]);
}

int	if_one_cmd(t_cmds *aux, t_pipe_var *info, char ***envp)
{
	int	i;

	i = 0;
	if (!aux->content)
		i = 1;
	if (!is_builtin(aux->content) && aux->content)
	{
		info->path = search_path(aux->content[0], *envp);
		i = 1;
	}
	g_common.pid = info->pid;
	if (is_builtin(aux->content))
		if_is_one_builtin_cmd(aux, info, envp);
	if (i == 1)
	{
		info->aux_fds[READ_END] = dup(STDIN_FILENO);
		info->aux_fds[WRITE_END] = dup(STDOUT_FILENO);
		only_son(info[0], aux, envp);
		dup2(info->aux_fds[READ_END], STDIN_FILENO);
		close(info->aux_fds[READ_END]);
		dup2(info->aux_fds[WRITE_END], STDOUT_FILENO);
		close(info->aux_fds[WRITE_END]);
	}
	return (i);
}
