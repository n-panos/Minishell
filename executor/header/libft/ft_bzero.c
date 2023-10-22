/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 18:20:02 by ipanos-o          #+#    #+#             */
/*   Updated: 2020/12/23 13:00:12 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// llenar de 0s un string de longitud conocida

void	ft_bzero(void *str, size_t n)
{
	char	*ptr;

	ptr = (char *)str;
	while (n)
	{
		*ptr = '\0';
		ptr++;
		n--;
	}
}
