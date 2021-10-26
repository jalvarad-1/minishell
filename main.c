# include "minishell.h"

t_global g_common;
HIST_ENTRY ** the_history_list;

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
		i++;
		env_v[i] = NULL;
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

int main (int argc, char **argv, char **envp)
{
	char *str;
	char **env_v;

	env_v = create_envp(envp);
	signal_receiver();
	while (1)
	{
		str = print_promt();
		if (ft_strcmp(str, ""))
		{
			built_in_identifier(str, &env_v);
		}
		free(str);
	}
}
