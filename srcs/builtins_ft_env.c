/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:35:28 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/02 10:35:39 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_quotation_marks(char *env, size_t add)
{
	char	*aux;
	int		i;
	int		j;

	i = 0;
	j = 0;
	aux = ft_calloc(sizeof(char), ft_strlen(env) + add);
	if (!aux)
		return ;
	while (env[i] && env[i] != '=')
		aux[j++] = env[i++];
	if (add == 3)
	{
		aux[j++] = env[i++];
		aux[j++] = '"';
		while (env[i])
			aux[j++] = env[i++];
		aux[j] = '"';
	}
	printf("declare -x %s\n", aux);
	free(aux);
}

static void	print_export(char **env)
{
	int		i;
	size_t	add;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			add = 3;
		else
			add = 1;
		add_quotation_marks(env[i], add);
		i++;
	}
}

static void	order_export(char **env)
{
	int			i;
	int			j;
	int			k;
	char		*aux;

	k = ft_split_len(env);
	i = 0;
	while (i < k)
	{
		j = i + 1;
		while (j < k)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				aux = env[j];
				env[j] = env[i];
				env[i] = aux;
			}
			j++;
		}
		i++;
	}
	print_export(env);
}

void	ft_env(char **env, bool assigned, int f_or_s)
{
	int		i;
	char	**ptr;

	i = 0;
	ptr = NULL;
	if (assigned)
	{
		while (env[i])
		{
			if (ft_strchr(env[i], '='))
				printf("%s\n", env[i]);
			i++;
		}
	}
	else
	{
		ptr = doublepointer_dup(env);
		order_export(ptr);
		free_matrix(ptr);
	}
	g_common.exit_status = 0;
	if (!f_or_s)
		exit(0);
}
