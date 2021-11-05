# include "minishell.h"

//En esencia esta funcion va a comprobar que la sintaxis de los operadores sea correcta
int	operator_identifier(char **str)
{
	size_t	i;
	size_t	j;

	while (str[i])
	{
		while (str[i][j])
		{

			j++;
		}
		i++;
	}
	return (1);
}
