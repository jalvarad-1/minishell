#include "minishell.h"

void make_out_redirections(t_pipe_var *info, t_fds *outputs)
{
	char			buffer;
	int i;

	i = 0;
	if (!outputs)
		return ;
	while (outputs && outputs[i].fds)
	{
		if (outputs[i].is_hdoc == 0)
		{
			info->fd1 = open(outputs[i].fds, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (info->fd1 == -1)
			{
				free(info->path);
				info->path = NULL;
				ft_putstr_fd("pipex: ", 1);
				ft_putstr_fd(outputs[i].fds, 1);
				ft_putstr_fd(": No such file or directory or permission denied\n",
					 1);
				return ;
			}
			dup2(info->fd1, STDOUT_FILENO);
			close(info->fd1);
			i++;
		}
		else if (outputs[i].is_hdoc == 1)
		{
			info->fd1 = open(outputs[i].fds, O_RDWR | O_CREAT, 0644);
			if (info->fd1 == -1)
			{
				free(info->path);
				info->path = NULL;
				ft_putstr_fd("pipex: ", 1);
				ft_putstr_fd(outputs[i].fds, 1);
				ft_putstr_fd(": No such file or directory or permission denied\n",
					 1);
				return ;
			}
			while (read(info->fd1, &buffer, 1))
				;
			dup2(info->fd1, STDOUT_FILENO);
			close(info->fd1);
			i++;
		}
	}
}

void make_in_redirections(t_pipe_var *info, t_fds *inputs, char **env)
{
	int i;
	int b;

	i = 0;
	if (!inputs)
		return ;
	while (inputs && inputs[i].fds)
	{
		if (inputs[i + 1].fds)
			b = dup(STDIN_FILENO);
		if (inputs[i].is_hdoc == 0)
		{
			info->fd1 = open(inputs[i].fds, O_RDONLY);
			if (info->fd1 == -1)
			{
				free(info->path);
				info->path = NULL;
				ft_putstr_fd("pipex: ", 1);
				ft_putstr_fd(inputs[i].fds, 1);
				ft_putstr_fd(": No such file or directory or permission denied\n",
					 1);
				close(b);
				return ;
			}
			dup2(info->fd1, STDIN_FILENO);
			close(info->fd1);
			if (inputs[i + 1].fds)
			{
				dup2(b, STDIN_FILENO);
				close(b);
			}
		}
		//printf("%s", inputs[i +1].fds);
		if (inputs[i].is_hdoc == 1)
		{
			ft_heredoc(inputs[i].fds, env, inputs[i].expand);
			if (inputs[i + 1].fds)
			{
				dup2(b, STDIN_FILENO);
				close(b);
			}
		}
		i++;
	}
}

void close_unnecessary(t_pipe_var info, int a, int b)
{
	int i;

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
	son_signal();
	make_in_redirections(&info, cmd->input_fd, *envp);
	if (info.fd1 == -1)
	{
		close_unnecessary(info, -8, -8);
		exit (-1);
	}
	make_out_redirections(&info, cmd->output_fd);
	if (info.fd1 == -1)
	{
		close_unnecessary(info, -8, -8);
		exit (-1);
	}
	execve(info.path, cmd->content, *envp);
	exit (0);
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
		make_out_redirections(&info, cmd->output_fd);
		if (info.fd1 == -1)
		{
			close_unnecessary(info, -8, -8);
			exit (-1);
		}
		close_unnecessary(info, info.fd2[0][READ_END], info.fd2[0][WRITE_END]);
	info.pid = fork();
	if (info.pid == -1)
		exit(-1);
	if (info.pid == 0)
	{
		son_signal();
		close(info.fd2[0][READ_END]);
		built_in_identifier(cmd->content, envp, 0);
		execve(info.path, cmd->content, *envp);
		exit (0);
	}
}

void	kamikaze_sonX(t_pipe_var info, t_cmds *cmd, char ***envp)
{
	dup2(info.fd2[info.l_p][READ_END], STDIN_FILENO);
	close(info.fd2[info.l_p][READ_END]);
	make_in_redirections(&info, cmd->input_fd, *envp);
		//close_unnecessary(info, info.fd2[info.l_p][READ_END], info.fd2[info.n_p][WRITE_END]);
	if (info.fd1 == -1 )
	{
		close_unnecessary(info, -8, -8);
		exit (-1);
	}
	dup2(info.fd2[info.n_p][WRITE_END], STDOUT_FILENO);
	close(info.fd2[info.n_p][WRITE_END]);
	make_out_redirections(&info, cmd->output_fd);
	if (info.fd1 == -1)
	{
		close_unnecessary(info, -8, -8);
		exit (-1);
	}
	info.pid = fork();
	if (info.pid == -1)
		exit(-1);
	if (info.pid == 0)
	{
		son_signal();
		close_unnecessary(info, info.fd2[info.l_p][READ_END], info.fd2[info.n_p][WRITE_END]);
		built_in_identifier(cmd->content, envp, 0);
		execve(info.path, cmd->content, *envp);
		exit (1);
	}
}

void	kamikaze_son2(t_pipe_var info, t_cmds *cmd, char ***envp)
{
	dup2(info.fd2[info.l_p][READ_END], STDIN_FILENO);
	close_unnecessary(info, -7, -7);
	make_in_redirections(&info, cmd->input_fd, *envp);
	if (info.fd1 == -1)
	{
		close_unnecessary(info, -8, -8);
		exit (-1);
	}
	make_out_redirections(&info, cmd->output_fd);
	if (info.fd1 == -1)
	{
		ft_putstr_fd("pipex: ", 1);
		ft_putstr_fd(": Permission denied\n", 1);
		close_unnecessary(info, -8, -8);
		exit (-1);
	}
	info.pid = fork();
	if (info.pid == -1)
		exit(-1);
	if (info.pid == 0)
	{
		son_signal();
		built_in_identifier(cmd->content, envp, 0);
		execve(info.path, cmd->content, *envp);
		exit (1);
	}
}

void	psycho_parent(t_pipe_var info, t_cmds *cmd, char ***envp)
{
	parent_signal();
	kamikaze_son2(info, cmd, envp);
	close(info.fd2[info.l_p][READ_END]);
}

int		**create_doble_array(t_cmds *cmd)
{
	int **pipe_array;
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

void	pipex(char ***envp, t_cmds *cmd)
{
	t_pipe_var	info;
	t_cmds		*aux;
	int i;

	i = 0;
	info.size = ft_lstsize(cmd) - 1;
	info.fd2 = create_doble_array(cmd);
	info.pid = 1;
	info.path = NULL;
	aux = cmd;
	i = 0;
	info.fd1 = -42;
	int b;
	int c;
	if (aux && !info.size)
	{
		if (!aux->content)
		{
			info.pid = fork();
			i = 1;
		}
		if (!is_builtin(aux->content) && aux->content)
		{
			info.path = search_path(aux->content[0], *envp);
			info.pid = fork();
			i = 1;
		}
		g_common.pid = info.pid;
		if (is_builtin(aux->content))
		{
			info.aux_fds[READ_END] = dup(STDIN_FILENO);
			make_in_redirections(&info, cmd->input_fd, *envp);
			info.aux_fds[WRITE_END] = dup(STDOUT_FILENO);
			make_out_redirections(&info, cmd->output_fd);
			if (info.fd1 != -1)
				built_in_identifier(aux->content, envp, 1);
			dup2(info.aux_fds[READ_END],STDIN_FILENO);
			close(info.aux_fds[READ_END]);
			dup2(info.aux_fds[WRITE_END], STDOUT_FILENO);
			close(info.aux_fds[WRITE_END]);
		}
		if (info.pid == 0)
		{
			only_son(info, aux, envp);
		}
	}
	while (aux && info.size > 0)
	{
		b = dup(STDIN_FILENO);
		c = dup(STDOUT_FILENO);
		if (i < info.size)
			pipe(info.fd2[i]);
		if (!is_builtin(aux->content))
			info.path = search_path(aux->content[0], *envp);
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
		while (d < i - 1)
			free(info.fd2[d++]);
	free(info.fd2);
	while (info.pid != 0 && i > 0)
	{
		wait(&g_common.exit_status);
//		g_common.exit_status = info.status;
		i--;
	}
	g_common.pid = 0;
}
