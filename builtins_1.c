#include "minishell.h"

/*Necesitamos el PATH, Jose sabe como va eso*/
/*static void	pwd_func(void)
{
	char *str;

//	str = getcwd(Esto es el path, Esto la longitud de la string)
	printf("%s\n", str);
	free(str);
}*/

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

/*static void	unset_func(void)
{
	Se carga completamente la variable que le pongas
	No se puede hacer unset de una variable READ_ONLY
}*/

void	built_in_identifier(char *str)
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
		printf("unset command detected\n");
	else if (!ft_strcmp(split[0], "env"))
		printf("env command detected\n");
	else if (!ft_strcmp(split[0], "exit"))
		printf("exit command detected\n");
	else
		printf("command not found\n");
	//////////falta liberar todo el churro del split
}
