#include "minishell.h"
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

void	only_son(t_pipe_var info, char **argv, char ***envp)
{
	if (info.fd1 == -1)
	{
		free(info.path);
		info.path = NULL;
		ft_putstr_fd("pipex: ", 1);
		ft_putstr_fd(": No such file or directory or permission denied\n", 1);
	}

	execve(info.path, argv, *envp);
	exit (0);
}

void	kamikaze_son1(t_pipe_var info, char **argv, char ***envp)
{
	if (info.fd1 == -1)
	{
		free(info.path);
		info.path = NULL;
		ft_putstr_fd("pipex: ", 1);
		ft_putstr_fd(": No such file or directory or permission denied\n", 1);
	}
	close_unnecessary(info, info.fd2[0][READ_END], info.fd2[0][WRITE_END]);
	close(info.fd2[0][READ_END]);
	dup2(info.fd2[0][WRITE_END], STDOUT_FILENO);
	close(info.fd2[0][WRITE_END]);
	built_in_identifier(argv, envp, 0);
	execve(info.path, argv, *envp);
	exit (0);
}

void	kamikaze_sonX(t_pipe_var info, char **argv, char ***envp)
{
	if (info.fd1 == -1)
	{
		ft_putstr_fd("pipex: ", 1);
		ft_putstr_fd(": Permission denied\n", 1);
		exit(-1);
	}
	close_unnecessary(info, info.fd2[info.l_p][READ_END], info.fd2[info.n_p][WRITE_END]);
	dup2(info.fd2[info.l_p][READ_END], STDIN_FILENO);
	close(info.fd2[info.l_p][READ_END]);
	//system("lsof -c pipex");
	dup2(info.fd2[info.n_p][WRITE_END], STDOUT_FILENO);
	close(info.fd2[info.n_p][WRITE_END]);
	built_in_identifier(argv, envp, 0);
	execve(info.path, argv, *envp);
	exit (1);
}

void	kamikaze_son2(t_pipe_var info, char **argv, char ***envp)
{
	if (info.fd1 == -1)
	{
		ft_putstr_fd("pipex: ", 1);
		ft_putstr_fd(": Permission denied\n", 1);
		exit(-1);
	}
	close_unnecessary(info, info.fd2[info.l_p][READ_END], -7);
	dup2(info.fd2[info.l_p][READ_END], STDIN_FILENO);
	close(info.fd2[info.l_p][READ_END]);
	built_in_identifier(argv, envp, 0);
	execve(info.path, argv, *envp);
	exit (1);
}

void	psycho_parent(t_pipe_var info, char **argv, char ***envp)
{
	info.pid = fork();
	if (info.pid == -1)
		exit(-1);
	if (info.pid == 0)
		kamikaze_son2(info, argv, envp);
	else
		close(info.fd2[info.l_p][READ_END]);
}

int		**create_doble_array(t_cmds *cmd)
{
	t_cmds	*aux;
	int **pipe_array;
	int		i;
	int		b;
	i = 0;
	aux = cmd;
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
	info.path = NULL;
	close (19);
	close (21);
	aux = cmd;
	i = 0;
	if (aux && !info.size)
	{
		if (!is_builtin(aux->content))
		{
			info.path = search_path(aux->content[0], *envp);
			info.pid = fork();
		}
		g_common.pid = info.pid;
		if (is_builtin(aux->content))
		{
			built_in_identifier(aux->content, envp, 1);
		}
		if (info.pid == 0)
		{
			//signal(SIGINT, SIG_DFL);
			only_son(info, aux->content, envp);
		}
		i = 1;
	}

	while (aux && info.size > 0)
	{
		if (i < info.size)
			pipe(info.fd2[i]);
		if (!is_builtin(aux->content))
			info.path = search_path(aux->content[0], *envp);
		if (aux->next)
			info.pid = fork();
		//g_common.pid = info.pid
		if (info.pid == -1)
			exit(-1);
		if (aux->next && info.pid == 0 && i == 0)
			kamikaze_son1(info, aux->content, envp);
		if (aux->next && i != 0 && info.pid == 0)
			kamikaze_sonX(info, aux->content, envp);
		if (!aux->next && info.pid != 0)
			psycho_parent(info, aux->content, envp);
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
	}
	while (info.pid != 0 && i > 0)
	{
		wait(&info.status);
		i--;
	}
	g_common.pid = 0;
}
