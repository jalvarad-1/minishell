/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:37:12 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/02 10:37:16 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**destroy_var(char **var, int pos)
{
	char		**tmp;
	size_t		i;
	size_t		j;
	size_t		len;

	i = 0;
	j = 0;
	len = ft_split_len(var);
	tmp = (char **)ft_calloc(sizeof(char *), (len));
	if (!tmp)
		return (0);
	while (i < len)
	{
		if ((int)i != pos)
		{
			tmp[j] = ft_strdup(var[i]);
			j++;
		}
		free(var[i]);
		i++;
	}
	free(var);
	return (tmp);
}

char	*cut_compare(char *str)
{
	char	*aux;
	size_t	len;

	len = 0;
	while (str[len] != '=' && str[len])
		len++;
	aux = ft_calloc(sizeof(char), len + 1);
	ft_strncpy(aux, str, len);
	return (aux);
}

int	locate_var(char **env, char *str)
{
	char	*aux;
	char	*tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		aux = cut_compare(env[i]);
		tmp = cut_compare(str);
		if (!ft_strcmp(aux, tmp))
		{
			free(aux);
			free(tmp);
			return (i);
		}
		free(aux);
		free(tmp);
		i++;
	}
	return (-1);
}

void	ft_unset(char **str, char ***env, int f_or_s)
{
	size_t		i;
	int			j;

	i = 1;
	j = -1;
	if (!str[i])
		return ;
	while (str[i])
	{
		if (check_format(str[i]))
		{
			j = locate_var(*env, str[i]);
			if (j >= 0)
				*env = destroy_var(*env, j);
			g_common.exit_status = 0;
		}
		else
			printf("export: `%s': not a valid identifier\n", str[i]);
		i++;
	}
	if (!f_or_s)
		exit (0);
}
