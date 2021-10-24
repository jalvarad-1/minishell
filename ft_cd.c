#include "minishell.h"

void	ft_cd(char ***env_v, char **str)
{
	int	i;

	i = 1;
	if (str[i] && str[i][0])
	{
		chdir(str[i]);
		printf("|%s|puta ---", str[i]);
	}
	else
	{
		return ;
	}
}
