/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 15:55:24 by robrodri          #+#    #+#             */
/*   Updated: 2021/05/30 15:55:26 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		n;
	int		a;
	int		len;
	char	*aux_s1;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	n = 0;
	a = 0;
	aux_s1 = malloc(sizeof(char) * len + 1);
	if (!aux_s1)
		return (0);
	ft_memcpy(aux_s1, s1, ft_strlen(s1) + 1);
	while (aux_s1[a] != '\0')
		a++;
	while (s2[n] != '\0')
	{
		aux_s1[a + n] = s2[n];
		n++;
	}
	aux_s1[a + n] = '\0';
	return (aux_s1);
}
/*char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	if (s1 == 0)
		return ((char *) s2);
	if (s2 == 0)
		return ((char *) s1);
	str = ft_calloc ((ft_strlen(s1) + ft_strlen(s2) + 2), sizeof(char));
	if (str == 0)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}*/
