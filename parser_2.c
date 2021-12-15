#include "minishell.h"

static void	move_quote_n_count(char **str, t_iterator *i, t_parse *prs)
{
	while (str[i->i][i->j])
	{
		if (str[i->i][i->j] == '"')
		{
			prs->d_q++;
			i->j++;
			while (str[i->i][i->j] && str[i->i][i->j] != '"')
				i->j++;
		}
		else if (str[i->i][i->j] == '\'')
		{
			prs->s_q++;
			i->j++;
			while (str[i->i][i->j] && str[i->i][i->j] != '\'')
				i->j++;
		}
		else
			i->j++;
	}
}

static int	unquoted_marks(char **str)
{
	t_iterator	i;
	t_parse		prs;

	prs = (t_parse){0, 0, 0, 0};
	i = (t_iterator){0, 0, 0, 0};
	while (str[i.i])
	{
		i.j = 0;
		move_quote_n_count(str, &i, &prs);
		i.i++;
	}
	if (prs.s_q % 2 || prs.d_q % 2)
	{
		printf("Error, unclosed quotation marks\n");
		return (0);
	}
	return (1);
}

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

void	ft_expand(char **token, char **env, int flag)
{
	ft_dollar_detect(token, env, flag);
	ft_trim_quotes(token, flag);
}

static int	dismember(char **cmd, char **env, t_cmds **table)
{
	int		i;
	t_fds	*ins;
	t_fds	*outs;
	char	**token;

	i = 0;
	token = NULL;
	while (cmd[i])
	{
		token = ft_mod_split(cmd[i], ' ');
		if (!operator_identifier(token))
		{
			free_matrix(cmd);
			free_matrix(token);
			ft_free_table(table);
			return (0);
		}
		ins = ft_get_inputs(&token, '<', env);
		outs = ft_get_inputs(&token, '>', env);
		ft_expand(token, env, 0);
		save_cmd(table, token, ins, outs);
		i++;
	}
	return (1);
}

int	get_command_table(char *str, char **env, t_cmds **table)
{
	char	**cmd;

	if (!rev_vertial_bars(str))
		return (0);
	cmd = ft_mod_split(str, '|');
	if (!unquoted_marks(cmd))
	{
		free_matrix(cmd);
		return (0);
	}
	if (!dismember(cmd, env, table))
		return (0);
	free_matrix(cmd);
	return (1);
}
