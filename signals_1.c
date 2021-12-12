/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:45:24 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/11 16:45:27 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signal)
{
	(void)signal;
	if (g_common.pid == 0)
		write(1, "\n", 1);
	if (!g_common.is_cmd)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_receiver(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	son_signal(void)
{
	signal(SIGINT, SIG_DFL);
}

void	parent_signal(void)
{
	signal(SIGINT, SIG_IGN);
}
