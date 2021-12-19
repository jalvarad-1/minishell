/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 15:51:31 by robrodri          #+#    #+#             */
/*   Updated: 2021/05/30 15:51:37 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*x;
	unsigned char	*y;

	x = ((unsigned char *)dst);
	y = ((unsigned char *)src);
	if (x == y)
	{
		return (dst);
	}
	else if (x > y)
	{
		while (len)
		{
			x[len - 1] = y[len - 1];
			len--;
		}
		return (dst);
	}
	else
		return (ft_memcpy(dst, src, len));
}
