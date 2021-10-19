/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 15:56:28 by robrodri          #+#    #+#             */
/*   Updated: 2021/05/30 15:56:29 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			z;
	unsigned int	nb;

	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write (fd, "-", sizeof(char));
		n = n * (-1);
	}
	nb = (unsigned int) n;
	if (nb > 9)
	{
		ft_putnbr_fd((nb / 10), fd);
		z = '0' + (nb % 10);
		write (fd, &z, sizeof(char));
	}
	else
	{
		z = nb + '0';
		write (fd, &z, sizeof(char));
	}
}
