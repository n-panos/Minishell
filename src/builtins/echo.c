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

int	ft_print_echo(char *str, int flag);

int	ft_exec_echo(char *str)
{
	char	**aux;
	int		i;
	int		ret;


	if (str == NULL)
		return (1);
	aux = ft_split(str, ' ');
	i = 0;
	ret = 0;
	while (aux[i])
		i++;
	if (i == 1)
		ft_print_echo(" ", 0);
	if (i == 2)
		ft_print_echo(aux[1], 0);
	else if (i == 3 && ft_strncmp(aux[1], "-n", ft_strlen("-n")) == 0)
		ft_print_echo(aux[2], 1);
	else
		ret = 2;
	ft_free_mtx(aux);
	return (ret);
}

int	ft_print_echo(char *str, int flag)
{
	if (flag == 0)
		printf("%s\n", str);
	else if (flag == 1)
		printf("%s", str);
	return (0);
}
