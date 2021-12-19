/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 15:52:53 by robrodri          #+#    #+#             */
/*   Updated: 2021/05/30 15:52:55 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	if (c == 0)
		return ((char *) &s[len]);
	while (len + 1 > 0)
	{
		if (s[len] == (char) c)
			return ((char *) &s[len]);
		len--;
	}
	return (0);
}
