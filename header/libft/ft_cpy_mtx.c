/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy_mtx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:29:45 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/03 12:47:42 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_mtx_line_cnt(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
	{
		i++;
	}
	return (i);
}

char	**ft_cpy_mtx(char **mtx)
{
	char	**ret_mtx;
	int		i;
	int		mtx_height;

	mtx_height = ft_mtx_line_cnt(mtx);
	ret_mtx = (char **)malloc(sizeof(char *) * mtx_height + 1);
	i = 0;
	while (mtx[i])
	{
		ret_mtx[i] = ft_strdup(mtx[i]);
		i++;
	}
	ret_mtx[i] = NULL;
	return (ret_mtx);
}
