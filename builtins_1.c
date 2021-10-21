#include "minishell.h"

void	built_in_identifier(char *str)
{
	if (!ft_strcmp(str, "echo"))
		printf("echo command detected\n");
	else if (!ft_strcmp(str, "cd"))
		printf("cd command detected\n");
	else if (!ft_strcmp(str, "pwd"))
		printf("pwd command detected\n");
	else if (!ft_strcmp(str, "export"))
		printf("export command detected\n");
	else if (!ft_strcmp(str, "unset"))
		printf("unset command detected\n");
	else if (!ft_strcmp(str, "env"))
		printf("env command detected\n");
	else if (!ft_strcmp(str, "exit"))
		printf("exit command detected\n");
}
