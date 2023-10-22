/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 15:07:21 by ipanos-o          #+#    #+#             */
/*   Updated: 2020/12/23 14:46:14 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//concatena dos strings en dst (añada lo que haya en src al final de dst)

size_t	ft_strlcat(char *dst, const char *src, size_t len)
{
	size_t	d;
	size_t	s;
	size_t	i;

	d = ft_strlen(dst);
	s = ft_strlen(src);
	if (len <= d)
		s += len;
	else
		s += d;
	i = 0;
	while (src[i] != '\0' && d + 1 < len)
	{
		dst[d] = src[i];
		i++;
		d++;
	}
	dst[d] = '\0';
	return (s);
}
