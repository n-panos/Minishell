/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:21:58 by ipanos-o          #+#    #+#             */
/*   Updated: 2020/12/23 14:06:28 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//copia en dst lo que haya en src con tamaño limite

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	if ((int)dst == '\0' && (int)src == '\0')
		return (dst);
	else
	{
		while (len--)
			*d++ = *s++;
		return (dst);
	}
}
