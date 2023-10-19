/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtx_cut.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:08:27 by nacho             #+#    #+#             */
/*   Updated: 2023/10/19 13:11:20 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// hace una copia de la matriz y le corta la linea indicada

char	**ft_mtx_cut(char **mtx, int cut)
{
	char	**ret_mtx;
	int		i;
	int		mtx_height;

	mtx_height = ft_mtx_line_cnt(mtx);
	ret_mtx = (char **)malloc(sizeof(char *) * mtx_height);
	i = 0;
	while (mtx[i])
	{
		if (i != cut)
			ret_mtx[i] = ft_strdup(mtx[i]);
		i++;
	}
	ret_mtx[i - 1] = NULL;
	return (ret_mtx);
}
