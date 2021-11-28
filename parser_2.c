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
			{
				prs.d_q++;
				j++;
				while (str[i][j] && str[i][j] != '"')
					j++;
			}
			else if (str[i][j] == '\'')
			{
				prs.s_q++;
				j++;
				while (str[i][j] && str[i][j] != '\'')
					j++;
			}
			else
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

//Hay que revisar esta funcion porque no esta guardando bien los comandos en la tabla ni crea mas de un NODO
static void	save_cmd(t_cmds **stack, char **argv, t_fds *ins, t_fds *outs)
{
	t_cmds	*tmp;
	if (*stack == NULL)
		*stack = ft_lstnew(argv, ins, outs);
	else
	{
		tmp = ft_lstnew(argv, ins, outs);
		ft_lstadd_back(stack, tmp);
	}
}


int	ft_trim_quotes(char **str, int out)
{
	size_t	i;
	size_t	j;
	int		flag;
	t_parse	prs;

	i = 0;
	flag = 0;
	prs = (t_parse){0, 0 ,0 ,0};
	if (!str)
		return(0);
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '"')
			{
				j++;
				flag = 1;
				while (str[i][j] != '"')
					j++;
				prs.d_q+=2;
			}
			else if (str[i][j] == '\'')
			{
				j++;
				flag = 1;
				while (str[i][j] != '\'')
					j++;
				prs.s_q+=2;
			}
			j++;
		}
		ft_trim_plus(&str[i], prs);
		if (out)
			return (flag);
		i++;
	}
	return (flag);
}

void	ft_expand(char **token, char **env, int flag)
{
	ft_dollar_detect(token, env, flag);
	// $$ te da el numero de proceso de bash. Deberiamos dar el ps de minishell?
	ft_trim_quotes(token, flag);
}

int	get_command_table(char *str, char **env, t_cmds **table)
{
	char	**cmd;
	char	**token;
	int		i;
	t_fds	*ins;
	t_fds	*outs;

	i = 0;
	ins = NULL;
	outs = NULL;
	if (!rev_vertial_bars(str))
		return (0);
	cmd = ft_mod_split(str, '|');
	if (!unquoted_marks(cmd))
	{
		free_matrix(cmd);
		return (0);
	}
	while (cmd[i])
	{
		token = ft_mod_split(cmd[i], ' ');
		if (!operator_identifier(token))
		{
			free(cmd);
			return (0);
		}
		ins = ft_get_inputs(&token, '<');
		outs = ft_get_inputs(&token, '>');
		ft_expand(&ins->fds, env, 1);
		ft_expand(&outs->fds, env, 1);
		ft_expand(token, env, 0);
		save_cmd(table, token, ins, outs);
		i++;
	}
/*	while (*table)
	{
		i = 0;
		while ((*table)->content[i])
			printf("%s\n", (*table)->content[i++]);
		*table = (*table)->next;
	}*/
	free_matrix(cmd);
	return (1);
}
