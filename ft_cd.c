/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:25:32 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/15 17:12:13 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	no_str_case(char **str, char ***env_v)
{
	int		i;

	i = locate_var(*env_v, "HOME");
	if (i >= 0 && ((*env_v)[i])[4] != 0)
	{
		g_common.exit_status = 0;
		*str = ft_strdup((*env_v)[i] + 5);
	}
	else
	{
		g_common.exit_status = 1;
		printf("Burrishell : cd: HOME not set\n");
	}
}

static void	is_str_case(char *aux, char ***env_v)
{
	int	i;
	int	j;

	j = locate_var(*env_v, "OLDPWD");
	i = locate_var(*env_v, "PWD");
	if (i >= 0 && j >= 0)
	{
		free((*env_v)[j]);
		(*env_v)[j] = ft_strjoin("OLDPWD", ((*env_v)[i]) + 3);
		free((*env_v)[i]);
		getcwd(aux, ARG_MAX);
		(*env_v)[i] = ft_strjoin("PWD=", aux);
	}
	else if (i < 0 && j >= 0)
	{
		free((*env_v)[j]);
		(*env_v)[j] = ft_strjoin("OLDPWD", "");
	}
	else if (i >= 0 && j < 0)
	{
		free((*env_v)[i]);
		getcwd(aux, ARG_MAX);
		(*env_v)[i] = ft_strjoin("PWD=", aux);
	}
	g_common.exit_status = 0;
}

void	ft_cd(char ***env_v, char **str, int f_or_s)
{
	char	aux[ARG_MAX];
	char	*aux_str;

	aux_str = NULL;
	if (str[1])
		aux_str = ft_strdup(str[1]);
	if (!aux_str)
		no_str_case(&aux_str, env_v);
	if (aux_str)
	{
		if (chdir(aux_str) == 0)
			is_str_case(aux, env_v);
		else
		{
			g_common.exit_status = 1;
			printf("Burrishell : cd: %s No such file or directory\n", aux_str);
		}
		free(aux_str);
	}
	if (!f_or_s)
		exit(0);
}
