/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:19:40 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/19 12:12:40 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**doublepointer_dup(char **array)
{
	char	**env_v;
	int		i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	env_v = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env_v)
		return (0);
	i = 0;
	while (array[i])
	{
		env_v[i] = ft_strdup(array[i]);
		i++;
	}
	env_v[i] = NULL;
	return (env_v);
}

static char	**create_envp(char **envp)
{
	char	**env_v;
	char	aux[ARG_MAX];
	int		i;

	i = 0;
	if (envp[i])
		env_v = doublepointer_dup(envp);
	else
	{
		env_v = ft_calloc(sizeof(char *), 2);
		getcwd(aux, ARG_MAX);
		env_v[i] = ft_strjoin("PWD=", aux);
	}
	return (env_v);
}

static char	*print_promt(void)
{
	char	*str;

	g_common.is_cmd = 0;
	str = readline("Burri_shell > ");
	if (!str)
	{
		write(1, "\b\b", 2);
		exit(errno);
	}
	if (*str)
	{
		add_history(str);
		g_common.is_cmd = 1;
	}
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	**env_v;
	t_cmds	*cmd_table;

	(void)argc;
	(void)argv;
	env_v = create_envp(envp);
	get_shell_level(&env_v);
	while (1)
	{
		signal_receiver();
		g_common.ctrl_c = 0;
		cmd_table = NULL;
		str = print_promt();
		if (ft_strcmp(str, ""))
		{
			if (get_command_table(str, env_v, &cmd_table))
				pipex(&env_v, cmd_table);
			ft_free_table(&cmd_table);
		}
		free(str);
	}
}
