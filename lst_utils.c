#include "minishell.h"

void	ft_free_table(t_cmds **table)
{
	t_cmds *aux;

	while(*table)
	{
		aux = (*table)->next;
		free_matrix((*table)->content);
		free_matrix((*table)->input_fd);
		free_matrix((*table)->output_fd);
		free(*table);
		*table = aux;
	}
}

t_cmds	*ft_lstnew(char **content, t_fds *fds)
{
	t_cmds	*a;

	a = malloc(sizeof(t_cmds));
	if (!a)
		return (NULL);
	a->content = content;
	a->input_fd = fds->ins;
	a->output_fd = fds->outs;
	a->heredoc_end = fds->h_end;
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

int	ft_lstsize(t_cmds *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
