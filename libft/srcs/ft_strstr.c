/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:17:09 by robrodri          #+#    #+#             */
/*   Updated: 2021/12/01 12:17:15 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0')
		return ((char *) haystack);
	i = 0;
	while (*haystack != '\0')
	{
		j = 0;
		while (*(haystack + j) == *(needle + j))
		{
			if (*(needle + j + 1) == '\0')
				return ((char *) haystack);
			j++;
		}
		i++;
		haystack++;
	}
	return (0);
}
