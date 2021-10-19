/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 15:51:21 by robrodri          #+#    #+#             */
/*   Updated: 2021/05/30 15:51:23 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		(((unsigned char *)dst)[i]) = (((unsigned char *)src)[i]);
		if ((((unsigned char *)src)[i]) == (unsigned char) c)
			return (dst + i + 1);
		i++;
	}
	return (0);
}
