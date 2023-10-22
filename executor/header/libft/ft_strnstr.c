/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 15:19:24 by ipanos-o          #+#    #+#             */
/*   Updated: 2020/12/23 15:19:26 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//busca palabra o frase en un string

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		j;
	size_t	t;
	int		nedlen;

	if (*needle == '\0')
		return ((char *)haystack);
	nedlen = ft_strlen(needle);
	j = 0;
	while (haystack[j] != '\0')
	{
		i = 0;
		t = j;
		while (needle[i] == haystack[t] && (len > t))
		{
			i++;
			if (i == nedlen)
				return ((char *)(haystack + j));
			t++;
		}
		j++;
	}
	return (NULL);
}
