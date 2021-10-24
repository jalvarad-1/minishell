#include "minishell.h"
/*en caso de chdir de -1 mostrar un mensaje de error ,,, falta cambiar las variables de entorno*/
void	ft_cd(char ***env_v, char **str)
{
	int	i;

	i = 1;
	if (str[i])
	{
		chdir(str[i]);
	}
	else
	{
		i = locate_var(*env_v, "HOME");
		if (i >= 0)
			chdir((*env_v)[i] + 5);
	}
}