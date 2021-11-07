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
void	ft_echo(char **str, int f_or_s)
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
	if (!f_or_s)
		exit (0);
}

////f_or_s = father_or_son 0 si es padre 1 si es hijo
void	built_in_identifier(char **argv, char ***env, int f_or_s)
{
	//char	**split;

	//split = ft_split(*str, ' ');
	if (!ft_strcmp(argv[0], "echo"))
		ft_echo(argv, f_or_s);
	else if (!ft_strcmp(argv[0], "cd"))
		ft_cd(env, argv, f_or_s);
	else if (!ft_strcmp(argv[0], "pwd"))
		ft_pwd(f_or_s);
	else if (!ft_strcmp(argv[0], "export"))
		ft_export(argv, env, f_or_s);
	else if (!ft_strcmp(argv[0], "unset"))
		ft_unset(argv, env, f_or_s);
	else if (!ft_strcmp(argv[0], "env"))
		ft_env(*env, 1, f_or_s);
	else if (!ft_strcmp(argv[0], "exit"))
		ft_exit(argv);
	//else
	//	printf("command not found\n");
	//free_matrix(split);
}

int	is_builtin(char **argv)
{

	if (!ft_strcmp(argv[0], "echo"))
		return (1);
	else if (!ft_strcmp(argv[0], "cd"))
		return (1);
	else if (!ft_strcmp(argv[0], "pwd"))
		return (1);
	else if (!ft_strcmp(argv[0], "export"))
		return (1);
	else if (!ft_strcmp(argv[0], "unset"))
		return (1);
	else if (!ft_strcmp(argv[0], "env"))
		return (1);
	else if (!ft_strcmp(argv[0], "exit"))
		return (1);
	return (0);
}
