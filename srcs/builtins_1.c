/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 12:39:40 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/12 12:39:42 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_matrix(char **str)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (!str)
		return ;
	len = ft_split_len(str);
	while (i < len)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	built_in_identifier(char **argv, char ***env, int f_or_s)
{
	if (!argv)
		return ;
	if (!ft_strcmp(argv[0], "echo"))
		ft_echo(argv, f_or_s);
	else if (!ft_strcmp(argv[0], "cd"))
		ft_cd(env, argv, f_or_s);
	else if (!ft_strcmp(argv[0], "pwd"))
		ft_pwd(f_or_s);
	else if (!ft_strcmp(argv[0], "export"))
		ft_export(argv, env, f_or_s);
	else if (!ft_strcmp(argv[0], "unset"))
		ft_unset(argv, env, f_or_s);
	else if (!ft_strcmp(argv[0], "env"))
		ft_env(*env, 1, f_or_s);
	else if (!ft_strcmp(argv[0], "exit"))
		ft_exit(argv);
}

int	is_builtin(char **argv)
{
	if (!argv)
		return (0);
	if (!ft_strcmp(argv[0], "echo"))
		return (1);
	else if (!ft_strcmp(argv[0], "cd"))
		return (1);
	else if (!ft_strcmp(argv[0], "pwd"))
		return (1);
	else if (!ft_strcmp(argv[0], "export"))
		return (1);
	else if (!ft_strcmp(argv[0], "unset"))
		return (1);
	else if (!ft_strcmp(argv[0], "env"))
		return (1);
	else if (!ft_strcmp(argv[0], "exit"))
		return (1);
	return (0);
}
