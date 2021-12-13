#include "minishell.h"

int	one_out_operator(t_fds *outputs, t_pipe_var *info, int i)
{
	info->fd1 = open(outputs[i].fds, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (info->fd1 == -1)
	{
		free(info->path);
		info->path = NULL;
		ft_putstr_fd("Burrishell: ", 1);
		ft_putstr_fd(outputs[i].fds, 1);
		ft_putstr_fd(": No such file or directory or permission denied\n",
			 1);
		return (0);
	}
	dup2(info->fd1, STDOUT_FILENO);
	close(info->fd1);
	return (1);
}

int	two_out_operator(t_fds *outputs, t_pipe_var *info, int i)
{
	char	buffer;

	info->fd1 = open(outputs[i].fds, O_RDWR | O_CREAT, 0644);
	if (info->fd1 == -1)
	{
		free(info->path);
		info->path = NULL;
		ft_putstr_fd("pipex: ", 1);
		ft_putstr_fd(outputs[i].fds, 1);
		ft_putstr_fd(": No such file or directory or permission denied\n",
			 1);
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

int	one_in_operator(t_fds *inputs, t_pipe_var *info, int i, int b)
{
	info->fd1 = open(inputs[i].fds, O_RDONLY);
	if (info->fd1 == -1)
	{
		free(info->path);
		info->path = NULL;
		ft_putstr_fd("pipex: ", 1);
		ft_putstr_fd(inputs[i].fds, 1);
		ft_putstr_fd(": No such file or directory or permission denied\n", 1);
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

void	two_in_operator(t_fds *inputs, int i, int b, char **env)
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
	b = 0;
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

void	close_unnecessary(t_pipe_var info, int a, int b)
{
	int	i;

	i = 0;
	while (i < info.size)
	{
		if (info.fd2[i][0] != a && info.fd2[i][0] != b)
			close(info.fd2[i][0]);
		if (info.fd2[i][1] != a && info.fd2[i][1] != b)
			close(info.fd2[i][1]);
		i++;
	}
}

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
			exit(2);
		son_signal();
		execve(info.path, cmd->content, *envp);
		exit (0);
	}
}

void	aux_kamikaze_son1(t_pipe_var info, t_cmds *cmd, char ***envp)
{
	info.pid = fork();
	if (info.pid == -1)
		exit(-1);
	if (info.pid == 0)
	{
		if (g_common.ctrl_c == 1)
			exit(0);
		son_signal();
		close(info.fd2[0][READ_END]);
		built_in_identifier(cmd->content, envp, 0);
		execve(info.path, cmd->content, *envp);
		exit (2);
	}
}

void	kamikaze_son1(t_pipe_var info, t_cmds *cmd, char ***envp)
{
	make_in_redirections(&info, cmd->input_fd, *envp);
	if (info.fd1 == -1)
	{
		close_unnecessary(info, -8, -8);
		exit (-1);
	}
	dup2(info.fd2[0][WRITE_END], STDOUT_FILENO);
	close(info.fd2[0][WRITE_END]);
	if (g_common.ctrl_c == 0)
		make_out_redirections(&info, cmd->output_fd);
	if (info.fd1 == -1)
	{
		close_unnecessary(info, -8, -8);
		exit (-1);
	}
	close_unnecessary(info, info.fd2[0][READ_END], info.fd2[0][WRITE_END]);
	aux_kamikaze_son1(info, cmd, envp);
}

void	aux_kamikaze_sonX(t_pipe_var info, t_cmds *cmd, char ***envp)
{
	info.pid = fork();
	if (info.pid == -1)
		exit(-1);
	if (info.pid == 0)
	{
		if (g_common.ctrl_c == 1)
			exit(2);
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
		exit (-1);
	}
	dup2(info.fd2[info.n_p][WRITE_END], STDOUT_FILENO);
	close(info.fd2[info.n_p][WRITE_END]);
	if (g_common.ctrl_c == 0)
		make_out_redirections(&info, cmd->output_fd);
	if (info.fd1 == -1)
	{
		close_unnecessary(info, -8, -8);
		exit (-1);
	}
	aux_kamikaze_sonX(info, cmd, envp);
}

void	aux_kamikaze_son2(t_pipe_var info, t_cmds *cmd, char ***envp)
{
	info.pid = fork();
	if (info.pid == -1)
		exit(-1);
	if (info.pid == 0)
	{
		if (g_common.ctrl_c == 1)
			exit(2);
		son_signal();
		built_in_identifier(cmd->content, envp, 0);
		execve(info.path, cmd->content, *envp);
		exit (1);
	}
}

void	kamikaze_son2(t_pipe_var info, t_cmds *cmd, char ***envp)
{
	if (!cmd->input_fd)
		dup2(info.fd2[info.l_p][READ_END], STDIN_FILENO);
	close_unnecessary(info, -7, -7);
	if (g_common.ctrl_c == 0)
		make_in_redirections(&info, cmd->input_fd, *envp);
	if (info.fd1 == -1)
	{
		close_unnecessary(info, -8, -8);
		exit (-1);
	}
	if (g_common.ctrl_c == 0)
		make_out_redirections(&info, cmd->output_fd);
	if (info.fd1 == -1)
	{
		ft_putstr_fd("pipex: ", 1);
		ft_putstr_fd(": Permission denied\n", 1);
		close_unnecessary(info, -8, -8);
		exit (-1);
	}
	aux_kamikaze_son2(info, cmd, envp);
}

void	psycho_parent(t_pipe_var info, t_cmds *cmd, char ***envp)
{
	parent_signal();
	kamikaze_son2(info, cmd, envp);
	close(info.fd2[info.l_p][READ_END]);
}

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

void	if_is_one_builtin_cmd(t_cmds *aux, t_pipe_var *info, char ***envp)
{
	info->aux_fds[READ_END] = dup(STDIN_FILENO);
	make_in_redirections(info, aux->input_fd, *envp);
	info->aux_fds[WRITE_END] = dup(STDOUT_FILENO);
	if (g_common.ctrl_c == 0)
		make_out_redirections(info, aux->output_fd);
	if (info->fd1 != -1 && g_common.ctrl_c == 0)
		built_in_identifier(aux->content, envp, 1);
	dup2(info->aux_fds[READ_END],STDIN_FILENO);
	close(info->aux_fds[READ_END]);
	dup2(info->aux_fds[WRITE_END], STDOUT_FILENO);
	close(info->aux_fds[WRITE_END]);
}

int	if_one_cmd(t_cmds *aux, t_pipe_var *info, char ***envp)
{
	int i;

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
		dup2(info->aux_fds[READ_END],STDIN_FILENO);
		close(info->aux_fds[READ_END]);
		dup2(info->aux_fds[WRITE_END], STDOUT_FILENO);
		close(info->aux_fds[WRITE_END]);
	}
	return (i);
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
		i = if_one_cmd(aux, &info, envp);
	while (aux && info.size > 0)
	{
		b = dup(STDIN_FILENO);
		c = dup(STDOUT_FILENO);
		if (i < info.size)
			pipe(info.fd2[i]);
		if (!is_builtin(aux->content))
		{
			if (aux->content)
				info.path = search_path(aux->content[0], *envp);
			else
				info.path = NULL;
		}
		if (aux->next && i == 0)
			kamikaze_son1(info, aux, envp);
		else if (aux->next && i != 0 )
			kamikaze_sonX(info, aux, envp);
		else if (!aux->next && info.pid != 0)
			psycho_parent(info, aux, envp);
		if (info.pid != 0)
		{
			if (info.path != NULL)
			{
				free(info.path);
				info.path = NULL;
			}
			if (i < info.size)
			{
				close(info.fd2[i][WRITE_END]);
				if (i > 0)
					close(info.fd2[info.l_p][READ_END]);
			}
			aux = aux->next;
			info.l_p = i;
			i++;
			info.n_p = i;
		}
		dup2(b, STDIN_FILENO);
		close(b);
		dup2(c, STDOUT_FILENO);
		close(c);
	}
	int d;
	d = 0;
	if (info.fd2 != NULL)
	{
		while (d < i - 1)
			free(info.fd2[d++]);
		free(info.fd2);
	}
	while (info.pid != 0 && i > 0)
	{
		wait(&g_common.exit_status);
		i--;
	}
	if (info.path)
		free(info.path);
	g_common.pid = 0;
}
