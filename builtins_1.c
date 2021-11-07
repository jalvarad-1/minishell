#include "minishell.h"

void	free_matrix(char **str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_split_len(str);
	while (i < len)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

/*Le falta el flag -n*/
void	ft_echo(char **str)
{
	int	i;

	i = 1;
	if (!str[i])
	{
		printf("\n");
		return ;
	}
	while (str[i])
		printf("%s ", str[i++]);
	printf("\n");
	exit (0);
}

void	built_in_identifier(char **str, char ***env)
{
	char	**split;

	split = ft_split(*str, ' ');
	if (!ft_strcmp(split[0], "echo"))
		ft_echo(split);
	else if (!ft_strcmp(split[0], "cd"))
		ft_cd(env, split);
	else if (!ft_strcmp(split[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(split[0], "export"))
		ft_export(split, env);
	else if (!ft_strcmp(split[0], "unset"))
		ft_unset(split, env);
	else if (!ft_strcmp(split[0], "env"))
		ft_env(*env, 1);
	else if (!ft_strcmp(split[0], "exit"))
		ft_exit(split);
	else
		printf("command not found\n");
	free_matrix(split);
}
