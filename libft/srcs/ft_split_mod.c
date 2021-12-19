/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 11:15:25 by jalvarad          #+#    #+#             */
/*   Updated: 2021/12/18 18:02:16 by robrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	aux2_ultimate_memcpy(const char *src, char *dst, int *i)
{
	dst[*i] = src[*i];
	(*i)++;
	while (src[*i] && src[*i] != '"')
	{
		dst[*i] = src[*i];
		(*i)++;
	}
}

static void	aux_ultimate_memcpy(const char *src, char *dst, char c)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != c)
	{
		if (src[i] == '\'')
		{
			dst[i] = src[i];
			i++;
			while (src[i] && src[i] != '\'')
			{
				dst[i] = src[i];
				i++;
			}
		}
		else if (src[i] == '"')
			aux2_ultimate_memcpy(src, dst, &i);
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

static char	*mod_ultimate_memcpy(const char *src, char c)
{
	size_t	i;
	char	*dst;

	i = 0;
	while (src[i] && src[i] != c)
	{
		move_out_quotes ((char **)&src, 0, (int *)&i);
		i++;
	}
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	aux_ultimate_memcpy(src, dst, c);
	return (dst);
}

static void	mod_locate_words(const char *s, char **aux, size_t words, char c)
{
	size_t	cont;
	size_t	cont2;

	cont = 0;
	cont2 = 0;
	while (cont < words)
	{
		while (s[cont2] == c)
			cont2++;
		aux[cont] = mod_ultimate_memcpy(s + cont2, c);
		while (s[cont2] && s[cont2] != c)
		{
			move_out_quotes ((char **)&s, 0, (int *)&cont2);
			cont2++;
		}
		cont++;
	}
	aux[cont] = NULL;
}

char	**ft_mod_split(const char *s, char c)
{
	size_t	words;
	char	**aux;

	if (!s)
		return (NULL);
	if (*s == 0)
	{
		aux = (char **)malloc(sizeof(char *));
		aux[0] = NULL;
		return (aux);
	}
	words = mod_word_count(s, c);
	if (!words)
		return (NULL);
	aux = (char **)malloc(sizeof(char *) * (words + 1));
	if (!aux)
		return (NULL);
	mod_locate_words(s, aux, words, c);
	return (aux);
}
