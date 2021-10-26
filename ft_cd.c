#include "minishell.h"
/*en caso de chdir de -1 mostrar un mensaje de error ,,, falta cambiar las variables de entorno*/
/*ya funciona y aparentemente replica el funcionamiento de la original falta soltar errores*/
void	ft_cd(char ***env_v, char **str)
{
	int	i;
	int j;
	char aux[ARG_MAX];
	char *aux_str;
	
	i = 1;
	aux_str = str[i];
	j = locate_var(*env_v, "OLDPWD");
	if (!aux_str)
	{
		i = locate_var(*env_v, "HOME");
		if (i >= 0 && ((*env_v)[i])[4] != 0)
		{
			aux_str = (*env_v)[i] + 5;
		}
	}
	if (aux_str)
	{
		if (chdir(aux_str) == 0)
		{
			i = locate_var(*env_v, "PWD");
			if (i>= 0 && j>= 0)
			{
				free((*env_v)[j]);
				(*env_v)[j] = ft_strjoin("OLDPWD", ((*env_v)[i]) + 3);
				free((*env_v)[i]);
				getcwd(aux, ARG_MAX);
				(*env_v)[i] = ft_strjoin("PWD=",aux);
			}
			else if (i < 0 && j >= 0)
			{
				free((*env_v)[j]);
				(*env_v)[j] = ft_strjoin("OLDPWD", "");
			}
			else if (i >= 0 && j < 0)
			{
				free((*env_v)[i]);
				getcwd(aux, ARG_MAX);
				(*env_v)[i] = ft_strjoin("PWD=",aux);
			}
		}
	}
}
