#include "minishell.h"

void	error_of_cmd(char **cmd)
{
	ft_putstr_fd(cmd[0], 1);
	ft_putstr_fd(": command not found\n", 1);
}

static char	*search_path_aux(char **split_paths, char **cmd)
{
	char	*aux;
	char	*path;
	int		i;

	i = 0;
	if (open(cmd[0], O_DIRECTORY) != -1)
	{
		printf("Burrishell: \"%s\": is a directory\n", cmd[0]);
		return (NULL);
	}
	if (access(cmd[0], X_OK) == 0)
		return (cmd[0]);
	while (split_paths[i])
	{
		aux = ft_strjoin(split_paths[i], "/");
		path = ft_strjoin(aux, cmd[0]);
		free(aux);
		aux = NULL;
		if (access(path, X_OK) == 0)
		{
			free_matrix(cmd);
			free_matrix(split_paths);
			return (path);
		}
		free(path);
		i++;
	}
	error_of_cmd(cmd);
	free_matrix(cmd);
	free_matrix(split_paths);
	return (0);
}

char	*search_path(char *argv, char **envp)
{
	char	*path;
	char	**split_paths;
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split(argv, ' ');
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
	{
		return (NULL);
	}
	split_paths = ft_split(envp[i] + 5, ':');
	path = search_path_aux(split_paths, cmd);
	return (path);
}
