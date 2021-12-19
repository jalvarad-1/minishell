/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:18:52 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/18 18:18:53 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_shell_level(char ***env_v, int pos)
{
	char	*search;
	char	*aux;
	int		nbr;
	char	*value;

	search = ft_strchr(env_v[0][pos], '=');
	nbr = ft_atoi(search + 1);
	if (nbr < 0)
		nbr = -1;
	value = ft_itoa(nbr + 1);
	aux = ft_strjoin("=", value);
	*env_v = change_var_value(env_v[0], aux, pos);
	free(value);
	free(aux);
}

void	get_shell_level(char ***env_v)
{
	char	**shl;
	int		pos;

	shl = ft_split("export SHLVL=1", ' ');
	pos = locate_var(*env_v, "SHLVL");
	if (pos > -1)
		change_shell_level(env_v, pos);
	else
		ft_export(shl, env_v, 1);
	free_matrix(shl);
}
