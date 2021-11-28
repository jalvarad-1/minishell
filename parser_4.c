#include "minishell.h"

//En esencia esta funcion va a comprobar que la sintaxis de los operadores sea correcta

/*
	1 - Encontrar el operador
	2 - Inmediatamente despues del operador debe encontrarse el output. Debe ser valido (alfanumerico o entre comillas)
*/
int	rev_vertial_bars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == '|')
			{
				printf("Burrishell: parse error near `|'\n");
				return (0);
			}
			while (str[i] && str[i] != '|')
			{
				move_out_quotes(&str, 0, &i);
				i++;
			}
		}
		else
			i++;
	}
	return (1);
}

int	aux_op_identifier(char **str, char opr, int *i, int *j)
{
	if (str[*i][(*j) + 1] == opr)
		(*j)++;
	(*j)++;
	if (!str[*i][*j])
	{
		(*i)++;
		(*j) = 0;
	}
	if (!str[*i])
	{
		printf("Burrishell: parse error near '\\n'\n");
		return (0);
	}
	if (str[*i][*j] == '<' || str[*i][*j] == '>')
	{
		printf("Burrishell: parse error near '%c'\n", str[*i][*j]);
		return (0);
	}
	while (str[*i][*j] && str[*i][*j] != '<' && str[*i][*j] != '>')
	{
		move_out_quotes(str, *i, j);
		(*j)++;
	}
	return (1);
}

int	operator_identifier(char **str)
{
	int	i;
	int	j;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			move_out_quotes(str, i, &j);
			if (str[i][j] == '<' || str[i][j] == '>')
			{
				if (!aux_op_identifier(str, str[i][j], &i, &j))
					return (0);
			}
			else
				j++;
		}
		i++;
	}
	return (1);
}
