/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 15:49:32 by robrodri          #+#    #+#             */
/*   Updated: 2021/05/30 15:55:17 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*aux;

	if (!s)
		return (0);
	if (start > ft_strlen(s) - 1)
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start - 1)
		len = ft_strlen(s) - start;
	aux = ft_calloc (len + 1, sizeof(char));
	if (aux == 0)
		return (0);
	i = 0;
	while (s)
	{
		if (i >= start)
		{
			ft_memcpy(aux, s + i, len);
			break ;
		}
		i++;
	}
	return (aux);
}
