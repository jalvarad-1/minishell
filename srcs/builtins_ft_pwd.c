/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:25:22 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/02 12:25:25 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(int f_or_s)
{
	char	drt[ARG_MAX];

	getcwd(drt, ARG_MAX);
	printf("%s\n", drt);
	g_common.exit_status = 0;
	if (!f_or_s)
		exit (0);
}
