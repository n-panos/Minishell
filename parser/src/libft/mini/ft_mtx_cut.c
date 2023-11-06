/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtx_cut.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:08:27 by nacho             #+#    #+#             */
/*   Updated: 2023/11/06 12:07:31 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// hace una copia de la matriz y le corta la linea indicada

char	**ft_mtx_cut(char **mtx, int cut)
{
	char	**ret_mtx;
	int		i;
	int		j;

	j = ft_mtx_line_cnt(mtx);
	ret_mtx = (char **)malloc(sizeof(char *) * j);
	i = 0;
	j = 0;
	while (mtx[i])
	{
		if (i != cut)
		{
			ret_mtx[j] = ft_strdup(mtx[i]);
			j++;
		}
		i++;
	}
	ret_mtx[j] = NULL;
	ft_mtx_free(mtx);
	return (ret_mtx);
}
