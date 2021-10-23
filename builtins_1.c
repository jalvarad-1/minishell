#include "minishell.h"
/*Le falta el flag -n*/
static void	echo_func(char **str)
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
}

void	built_in_identifier(char *str, char **env)
{
	char **split;

	split = ft_split(str, ' ');
	if (!ft_strcmp(split[0], "echo"))
		echo_func(split);
	else if (!ft_strcmp(split[0], "cd"))
		printf("cd command detected\n");
	else if (!ft_strcmp(split[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(split[0], "export"))
		printf("export command detected\n");
	else if (!ft_strcmp(split[0], "unset"))
		ft_unset(split, env);
	else if (!ft_strcmp(split[0], "env"))
		printf("env command detected\n");
	else if (!ft_strcmp(split[0], "exit"))
		printf("exit command detected\n");
	else
		printf("command not found\n");
	//////////falta liberar todo el churro del split
}
