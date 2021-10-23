#include "minishell.h"
/*Le falta el flag -n*/
static void	echo_func(char **str)
{
	int	i;

	i = 1;
	if (!str[i])
	{
		printf("\n");
		return ;
	}
	while (str[i])
		printf("%s ", str[i++]);
	printf("\n");
}

static size_t	get_env_len(char **env, char *str)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	while (env[i])
	{
		j = 0;
		len = 0;
		while (str[j])
		{
			if (!env[i][j])
				break ;
			if (str[j] == env[i][j])
				len++;
			j++;
		}
		if (j == (int)len)
			if (env[i][j] == '=')
				return (len);
		i++;
	}
	return (0);
}

void	ft_unset(char **str, char **env)
{
	int		i;
	int		j;
	int		len;

	i = 1;
	if (!str[i])
		return ;
	while (str[i])
	{
		j = 0;
		len = get_env_len(env, str[i]);
		if (!len)
			return ;
		while (env[j])
		{
			if (!ft_strncmp(str[i], env[j], len))
			{
				printf("He encontrado\n");
				break ;
			}
			j++;
		}
		i++;
	}
}

void	built_in_identifier(char *str, char **env)
{
	char **split;

	split = ft_split(str, ' ');
	if (!ft_strcmp(split[0], "echo"))
		echo_func(split);
	else if (!ft_strcmp(split[0], "cd"))
		printf("cd command detected\n");
	else if (!ft_strcmp(split[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(split[0], "export"))
		printf("export command detected\n");
	else if (!ft_strcmp(split[0], "unset"))
		ft_unset(split, env);
	else if (!ft_strcmp(split[0], "env"))
		printf("env command detected\n");
	else if (!ft_strcmp(split[0], "exit"))
		printf("exit command detected\n");
	else
		printf("command not found\n");
	//////////falta liberar todo el churro del split
}
