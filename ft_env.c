#include "minishell.h"

/*Proto-funcion para mostar el enviroment
y comprobar que set y unset funcionan correctamente*/

/*Assigned 1 = Mostrar solo variables asignadas*/
/*Assigned 0 = Ordenar y mostrar todas las variables precedido de declare -x*/
void	ft_env(char **env, bool assigned)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (assigned)
		{
			if (ft_strchr(env[i], '='))
				printf("%s\n", env[i]);
		}
		else
			printf("declare -x %s\n", env[i]);
		i++;
	}
}
