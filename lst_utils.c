#include "minishell.h"

t_cmds	*ft_lstnew(char **content)
{
	t_cmds	*a;

	a = malloc(sizeof(t_cmds));
	if (!a)
		return (NULL);
	a->content = doublepointer_dup(content);
	a->next = NULL;
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
