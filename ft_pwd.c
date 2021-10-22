#include "minishell.h"

void    ft_pwd()
{
	char drt[2000];

	getcwd(drt, 2000);
	printf("%s\n", drt);
}