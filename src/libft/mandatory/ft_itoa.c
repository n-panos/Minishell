/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:24:03 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/07/11 14:10:49 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_nb_len(int nb)
{
	int	size;

	size = 0;
	if (nb < 0)
	{
		size++;
		nb = -nb;
	}
	if (nb >= 0)
	{
		while (nb > 9)
		{
			nb = nb / 10;
			size++;
		}
		size++;
	}
	return (size);
}

char	*ft_minnb(char *itoa, char *min)
{
	int	i;

	itoa = (char *)malloc (sizeof(char) * 12);
	if (!itoa)
		return (0);
	i = 0;
	while (i < 11)
	{
		itoa[i] = min[i];
		i++;
	}
	itoa[i] = '\0';
	return (itoa);
}

char	*ft_itoa(int n)
{
	char	*itoa;
	int		digit;
	int		nb;

	itoa = NULL;
	if (n == -2147483648)
		return (ft_minnb(itoa, "-2147483648"));
	nb = n;
	digit = ft_nb_len(nb);
	itoa = malloc((digit + 1) * sizeof(char));
	if (n < 0)
		nb = -nb;
	if (!(itoa))
		return (0);
	itoa[digit] = '\0';
	while (digit > 0)
	{
		itoa[digit - 1] = (nb % 10) + '0';
		nb = nb / 10;
		digit--;
	}
	if (n < 0)
		itoa[digit] = '-';
	return (itoa);
}
