/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 15:55:37 by robrodri          #+#    #+#             */
/*   Updated: 2021/06/09 15:38:01 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_inset(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*ptr;

	if (s1 == 0)
		return (0);
	while (*s1)
	{
		if (ft_is_inset(set, *s1) == 1)
			s1++;
		else
			break ;
	}
	len = ft_strlen(s1);
	while (*(s1 + len - 1) && (len > 0))
	{
		if (ft_is_inset(set, *(s1 + len - 1)) == 1)
			len--;
		else
			break ;
	}
	ptr = ft_substr(s1, 0, len);
	return (ptr);
}
