/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:06:46 by ipanos-o          #+#    #+#             */
/*   Updated: 2020/12/23 14:13:11 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//rellena esa parte de memoria con el caracter "c"

void	*ft_memset(void *str, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = str;
	while (len--)
		*ptr++ = c;
	return (str);
}
