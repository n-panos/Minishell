/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtx_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:51:06 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/22 12:29:56 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_mtx_free(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
	{
		free(mtx[i]);
		mtx[i] = NULL;
		i++;
	}
	free(mtx);
	mtx = NULL;
}
