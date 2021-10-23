#include "minishell.h"

static int	locate_var(char **env, char *str)
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
				return (i);
		i++;
	}
	return (-1);
}

void	ft_unset(char **str, char **env)
{
	int		i;
	int		j;

	i = 1;
	if (!str[i])
		return ;
	while (str[i])
	{
		j = locate_var(env, str[i]);
		if (j >= 0)
			printf("Located %d\n", j);
//			destroy_var(env[j], str[j]);
		i++;
	}
}
