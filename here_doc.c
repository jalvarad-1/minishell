# include "minishell.h"

char	**ft_get_heredoc_cmd(char ***token, char *oprt)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (token[0][i])
	{
		j = 0;
		while (token[0][i][j])
		{
			move_out_quotes(token[0], i, &j);
			if (ft_strstr(token[0][i] + j, oprt))
		}
		i++;
	}
}
