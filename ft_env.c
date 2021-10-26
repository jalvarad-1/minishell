#include "minishell.h"

/*Proto-funcion para mostar el enviroment
y comprobar que set y unset funcionan correctamente*/

/*Assigned 1 = Mostrar solo variables asignadas*/
/*Assigned 0 = Ordenar y mostrar todas las variables precedido de declare -x*/
/*Export muestra cada valor entre comillas ""*/

/*TO-DO list :	Export debe poner "" en el valor de las variables*/

static char	*add_quotation_marks(char *env)
{
	char	*aux;
	int		i;

	i = 0;
	aux = ft_calloc(sizeof(char), ft_strlen(env) + 3);
	if (!aux)
		return (0);
	while(env[i] != '=')
	{
		aux[i] = env[i];
		i++;
	}
	aux[i++] = '"';
	while (env[i - 1])
	{
		aux[i] = env[i - 1];
		i++;
	}
	aux[i] = '"';
	return (aux);
}

static void	print_export(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", add_quotation_marks(env[i]));
		i++;
	}
}

static void	order_export(char **env)
{
	int			i;
	int			j;
	int			k;
	char		*aux;

	k = ft_split_len(env);
	i = 0;
	while (i < k)
	{
		j = i + 1;
		while (j < k)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				aux = env[j];
				env[j] = env[i];
				env[i] = aux;
			}
			j++;
		}
		i++;
	}
	print_export(env);
}

void	ft_env(char **env, bool assigned)
{
	int		i;
	char	**ptr;

	i = 0;
	ptr = NULL;
	if (assigned)
	{
		while (env[i])
		{
			if (ft_strchr(env[i], '='))
				printf("%s\n", env[i]);
			i++;
		}
	}
	else
	{
		ptr = doublepointer_dup(env);
		order_export(ptr);
		free_matrix(ptr);
	}
}
