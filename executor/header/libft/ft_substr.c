/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 17:50:01 by ipanos-o          #+#    #+#             */
/*   Updated: 2022/10/19 10:11:33 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	n;
	size_t	tam;

	if (s == NULL)
		return (NULL);
	tam = len + 1;
	if (ft_strlen(s) < len)
		tam = ft_strlen(s) - start + 1;
	str = malloc(sizeof(char) * tam);
	if (!str)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	n = 0;
	while (s[start] != '\0' && len)
	{
		str[n] = s[start];
		start++;
		n++;
		len--;
	}
	str[n] = '\0';
	return (str);
}
