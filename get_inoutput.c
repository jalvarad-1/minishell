#include "minishell.h"
int redirection_counter(char **token, char operator)
{
	int i;
	int j;
	int redirections;

	i = 0;
	redirections = 0;
	while (token && token[i])
	{
		j = 0;
		while (token[i][j])
		{
			if (token[i][j] == '\'' || token[i][j] == '"')
			{
				if (token[i][j] == '\'')
				{
					j++;
					while(token[i][j] && token[i][j] != '\'')
						j++;
				}
				else if (token[i][j] == '"')
				{
					j++;
					while (token[i][j] && token[i][j] != '"')
						j++;
				}
			}
			if (token[i][j] == operator)
				redirections++;
			j++;
		}
		i++;
	}
	return (redirections);
}

char **ft_get_inputs(char ***token)
{
	char **new_token;
	char **fds;
	int i;
	int j;

	i = redirection_counter(*token, '<');
	if (!i)
		return (NULL);
	fds = (char **)malloc(sizeof(char *) * (i + 1));
	if (!fds)
		return (NULL);
	i = 0;
	while(token[0][i])
	{
		j = 0;
		while (token[0][i][j])
		{

			j++;
		}
		i++;
	}
	return (fds);
}