# include "minishell.h"

//t_global g_common;

char **doublepointer_dup(char **array)
{
	char **env_v;
	int i;

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

char **create_envp(char **envp)
{
	char	**env_v;
	char	aux[ARG_MAX];
	int		i;

	i = 0;
	if (envp[i])
	{
		env_v = doublepointer_dup(envp);
	}
	else
	{
		env_v = (char **)malloc(sizeof(char *) * 2);
		getcwd(aux, ARG_MAX);
		env_v[i] = ft_strjoin("PWD=", aux);
		env_v[i + 1] = NULL;
	}
	return(env_v);
}

char	*print_promt(void)
{
	char *str;


	str = readline("Burri_shell > ");
	if (!str)
	{
		write(1, "\b\b", 2);
		exit(-1);
	}
	if (*str)
		add_history(str);
	return (str);
}

/*When the shell reads input, it proceeds through a sequence of operations.
If the input indicates the beginning of a comment, the shell ignores the comment symbol (‘#’),
and the rest of that line.

Otherwise, roughly speaking, the shell reads its input and divides the input
into words and operators, employing the quoting rules
to select which meanings to assign various words and characters.

The shell then parses these tokens into commands and other constructs,
removes the special meaning of certain words or characters, expands others,
redirects input and output as needed, executes the specified command,
waits for the command’s exit status, and makes that exit status available for further inspection
or processing.*/

int main (int argc, char **argv, char **envp)
{
	char	*str;
	char	**env_v;
	t_cmds	*cmd_table;

	env_v = create_envp(envp);
	signal_receiver();
	while (1)
	{
		cmd_table = NULL;
		str = print_promt();
		if (ft_strcmp(str, ""))
		{
			if (get_command_table(str, env_v, &cmd_table))
			{
//				printf("Entro\n");
//				printf("%s\n", cmd_table->content[1]);
				pipex(env_v, cmd_table);
//				built_in_identifier(cmd_table, &env_v);
			}
			//Liberar cmd_table
		}
		free(str);
	}
}
