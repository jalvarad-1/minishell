#include "minishell.h"
/* La ARG_MAX se pone pq en stackoverflow un jambo dice que es el maximo que cabe en una variable de netorno */
void    ft_pwd(void)
{
	char drt[ARG_MAX];

	getcwd(drt, ARG_MAX);
	printf("%s\n", drt);
}