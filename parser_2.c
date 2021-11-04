#include "minishell.h"

/* PARSE0 GAMEPLAN

-1 : Unclosed quotation marks
-2 : Lexer / Parser
-3 : Expand variables
-4 : Executer (DONE BY JALVARAD)
-5 : ?????
-6 : Profit

*/
static int	unquoted_marks(char **str)
{
	size_t	i;
	size_t	j;
	t_parse	prs;

	prs = (t_parse){0, 0, 0, 0};
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '"')
				prs.d_q++;
			else if (str[i][j] == '\'')
				prs.s_q++;
			j++;
		}
		i++;
	}
	if (prs.s_q % 2 || prs.d_q % 2)
	{
		printf("Error, unclosed quotation marks\n");
		return (0);
	}
	return (1);
}

/*static void	save_cmd(t_cmds **stack, char **argv)
{
	t_cmds	*tmp;

	if (*stack == NULL)
		*stack = ft_lstnew(argv);
	else
	{
		tmp = ft_lstnew(argv);
		ft_lstadd_back(stack, tmp);
	}
}*/


/*Las comillas son un claro caso de voy a joder al personal pero estoy seguro que no tenian mucha idea de como iba y lo dejaron asi

En cualquier caso, "" y '' Toman el VALOR LITERAL DE LO QUE TIENEN DENTRO
En otras palabras, las ultimas que se encuentran no existen en el ambito que nos concierne, pero tienen efecto
Eso funciona en las comillas simples y las comillas dobles
Un ejemplo practico "$USER" existe como USER (Robrodri/Jalvarad por la expansion) y '$USER' existe tal cual, $USER


*/
static void	ft_expand(char **token, char **env)
{
	ft_dollar_detect(token, env);
//	ft_trim_quotes(token);
	int	i = 0;
	while (token[i])
		printf("%s\n", token[i++]);
}

int	get_command_table(char *str, char **env, t_cmds *table)
{
	char	**cmd;
	char	**token;
	int		i;
//	char **aux1;
//	char **aux2;

	i = 0;
	cmd = ft_mod_split(str, '|');
	if (!unquoted_marks(cmd))
	{
		free_matrix(cmd);
		return (0);
	}
	while (cmd[i])
	{
		token = ft_mod_split(cmd[i], ' ');
///		if (!operator_indentifier(token))  /// retornara un entero (1 - correcto ; 0 mal)  y que se encargue de guardar los files
//			return;
//		aux = input ;
//		aux2 =auput ;
//		ft_outputs(table, &token);
		ft_expand(token, env);
//		save_cmd(&table, token, );
		free_matrix(token);
		i++;
	}
/*	while (table)
	{
		i = 0;
		while (table->content[i])
			printf("%s\n", table->content[i++]);
		table = table->next;
	}*/
	free_matrix(cmd);
	return (1);
}
