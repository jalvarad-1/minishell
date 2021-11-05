#include "minishell.h"

t_cmds	*ft_lstnew(char **content)
{
	t_cmds	*a;

	a = malloc(sizeof(t_cmds));
	if (!a)
		return (NULL);
	a->content = doublepointer_dup(content);
	a->next = NULL;
/*	int	i = 0;
	while (a)
	{
		while (a->content[i])
			printf("%s\n", a->content[i++]); //Lo hace bien
		a = a->next;
	}*/
	return (a);
}

void	ft_lstadd_back(t_cmds **lst, t_cmds *new)
{
	t_cmds	*aux;

	if (!*lst)
		*lst = new;
	else
	{
		aux = *lst;
		while (*lst)
		{
			if (!aux->next)
			{
				aux->next = new;
				break ;
			}
			aux = aux->next;
		}
	}
}
