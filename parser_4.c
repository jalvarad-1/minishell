# include "minishell.h"

//En esencia esta funcion va a comprobar que la sintaxis de los operadores sea correcta

/*
	1 - Encontrar el operador
	2 - Inmediatamente despues del operador debe encontrarse el output. Debe ser valido (alfanumerico o entre comillas)
*/
static int	forbbiden_chars(char c, char opr)
{
	if (c == opr || c == '\\' || c == ';')
		return (0)
	return (1);
}

static int	heredoc_parser(char **str, int *i, int *j, char opr)
{
	*j += 1;
	if (!str[*i][*j])
	{
		*i += 1;
		if (!str[*i])
			return (0);
		while (str[*i][*j])
		{
			if (str[*i][*j] == forbbiden_chars(str[*i][*j], opr))
				return (0);
			*j+=1;
		}
	}
	else
	{
		*j+= 1;
		while (str[*i][*j])
		{
			while (str[i][j])
			{
				if (forbbiden_chars(str[i][j], NULL))
					return (0);
				j+=1;
			}
		}
	}
	return (1);

}

int	operator_identifier(char **str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			move_out_quotes(str, i, &j);
			if (str[i][j] == '>')
			{
				j++;
				move_out_quotes(str, i, &j);
				if (str[i][j] == '>')
					if (!heredoc_parser(str, &i &j, '<'))
						return (0);
				else
				{
					j++;
					while (str[i][j])
					{
						if (!forbbiden_chars(str[i][j], '<'))
							return (0);
						j++;
					}
				}
					return (0);
			}
			else if (str[i][j] == '<')
			{
				move_out_quotes(str, i, &j);
				if (str[i][j] == '<')
					if (!heredoc_parser(str, &i, &j, '>'))
						return (0);
				else
				{
					j++;
					while (str[i][j])
					{
						if (forbbiden_chars(str[i][j], '<'))
							return (0);
						j++;
					}
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}
