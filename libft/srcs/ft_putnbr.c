/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 15:56:28 by robrodri          #+#    #+#             */
/*   Updated: 2021/06/12 17:42:56 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(long n)
{
	char			z;
	unsigned int	nb;

	if (n < 0)
	{
		write (1, "-", sizeof(char));
		n = n * (-1);
	}
	nb = (unsigned int) n;
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		z = '0' + (nb % 10);
		write (1, &z, sizeof(char));
	}
	else
	{
		z = nb + '0';
		write (1, &z, sizeof(char));
	}
}
