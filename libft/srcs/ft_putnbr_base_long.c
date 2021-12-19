/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 08:00:27 by jalvarad          #+#    #+#             */
/*   Updated: 2021/06/14 18:16:21 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	gest_errors(char *base)
{
	int	d;
	int	e;
	int	f;

	e = 0;
	d = ft_strlen(base);
	f = 0;
	if (d <= 1)
		return (1);
	while (base[e] != '\0' && base[f] != '\0' && d > 1 )
	{
		while (base[e] != '\0' && base[f] != '\0')
		{
			if ((base[e] == base[f] && e != f) || (base[f] == '+'\
				|| base[f] == '-'))
			{
				return (e);
			}
			f++;
		}
		e++;
		f = 0;
	}
	return (0);
}

int	ft_putnbr_base_long(unsigned long long nbr, char *base)
{
	int			a;
	int			b;
	static int	n;

	n = 0;
	if (gest_errors(base) == 0)
	{
		a = ft_strlen(base);
		if (nbr > 0)
		{
			ft_putnbr_base_long(nbr / a, base);
			b = nbr % a;
			write(1, &base[b], 1);
			n++;
		}
	}
	return (n);
}
