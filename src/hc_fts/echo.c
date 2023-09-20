/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:12:03 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/09/20 12:15:59 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

//	revisar la flag a ver como se recibe, en este 
//	caso 0 es sin flag, y 1 es con flag -n

int	ft_exec_echo(char *str, int flag)
{
	if (str == NULL)
		return (1);
	if (flag == 0)
		printf("%s\n", str);
	if (flag == 1)
		printf("%s", str);
	return (0);
}