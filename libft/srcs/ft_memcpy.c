/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 15:51:14 by robrodri          #+#    #+#             */
/*   Updated: 2021/05/30 15:51:16 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (src == 0 && dst == 0)
		return (0);
	if (src == dst)
		return (dst);
	i = 0;
	while (i < n)
	{
		(((unsigned char *)dst)[i]) = (((unsigned char *)src)[i]);
		i++;
	}
	return (dst);
}
