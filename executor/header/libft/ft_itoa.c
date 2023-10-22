/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:17:23 by ipanos-o          #+#    #+#             */
/*   Updated: 2022/09/14 12:26:22 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//recoge un entero y lo devuelve como caracteres en un string

static int	num_look(int n)
{
	int		len;
	long	nb;

	len = 1;
	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nb;

	i = 0;
	str = malloc(sizeof(char) * (num_look(n) + 1));
	if (!str)
		return (NULL);
	nb = n;
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	str[num_look(n) - i++] = '\0';
	while (nb > 9)
	{
		str[num_look(n) - i++] = 48 + (nb % 10);
		nb /= 10;
	}
	str[num_look(n) - i++] = 48 + (nb % 10);
	return (str);
}
