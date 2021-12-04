#include "minishell.h"

static char	*ft_conditions(char *str, size_t len)
{
	size_t	i;
	size_t	j;
	char	*aux;
	size_t	actual_len;

	i = 0;
	j = 0;
	actual_len = ft_strlen(str) - len;
	aux = ft_calloc(sizeof(char), actual_len + 2);
	if (!aux)
		return (0);
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				aux[j++] = str[i++];
			i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				aux[j++] = str[i++];
			i++;
		}
		else
			aux[j++] = str[i++];
	}
	return (aux);
}
void	ft_trim_plus(char **str, t_parse prs)
{
	char	*aux;
	size_t	len;

	len = prs.s_q + prs.d_q;
	aux = ft_conditions(*str, len);
	free(*str);
	*str = ft_strdup(aux);
	free(aux);
}
