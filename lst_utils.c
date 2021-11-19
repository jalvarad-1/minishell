#include "minishell.h"
void	free_struct(t_fds *content)
{
	int i;

	i = 0;
	if (!content)
		return ;
	while (content[i].fds) //// esta funcion libera el array de estructuras
	{
		free(content[i].fds);
		i++;
	}
	free(content);
}
void	ft_free_table(t_cmds **table)
{
	t_cmds *aux;

	while(*table)
	{
		aux = (*table)->next;
		free_matrix((*table)->content);
		free_struct((*table)->input_fd);
		free_struct((*table)->output_fd);
		free(*table);
		*table = aux;
	}
}

t_cmds	*ft_lstnew(char **content, t_fds *ins, t_fds *outs)
{
	t_cmds	*a;

	a = malloc(sizeof(t_cmds));
	if (!a)
		return (NULL);
	a->content = content;
	a->input_fd = ins;
	a->output_fd = outs;
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
