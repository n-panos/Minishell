/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:12:03 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/09/27 11:47:07 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

//	revisar la flag a ver como se recibe, en este 
//	caso 0 es sin flag, y 1 es con flag -n

int	ft_exec_echo(char **cmd_mtx)
{
	int		i;

	i = 0;
	if (ft_strlen(cmd_mtx[0]) != 4)
		return (2);
	while (cmd_mtx[i])
		i++;
	if (i == 1)
		printf(" \n");
	if (i == 2)
		printf("%s\n", cmd_mtx[1]);
	else if (i == 3 && ft_strncmp(cmd_mtx[1], "-n", ft_strlen("-n")) == 0)
		printf("%s", cmd_mtx[2]);
	else
		ret = 2;
	ft_free_mtx(aux);
	return (0);
}
