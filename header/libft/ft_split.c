/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 11:42:25 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/04/19 10:43:59 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//cuenta cuantos cortes hay

static int	ft_count_words(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		while (*str && *str == c)
			str++;
		if (*str && *str != c)
		{
			count++;
			while (*str && *str != c)
				str++;
		}
	}
	return (count);
}

//devuelve la palabra metida en un string separado

static char	*ft_word(const char *str, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

//corta el string en strings mas pequeños separados por el caracter "c"

char	**ft_split(const char *s, char c)
{
	char	**arr;
	int		i;

	i = 0;
	if (s == '\0')
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!arr)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			arr[i] = ft_word(s, c);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	arr[i] = NULL;
	return (arr);
}
