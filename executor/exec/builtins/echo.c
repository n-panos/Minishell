/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:19:04 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/31 09:19:05 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

int	ft_echo_args(char *arg);

int	ft_echo(char **cmd_mtx)
{
	int	i;
	int	f;
	int	j;

	i = 0;
	if (ft_strlen(cmd_mtx[0]) != 4)
		return (2);
	while (cmd_mtx[i])
		i++;
	if (i == 1)
	{
		printf("\n");
		return (0);
	}
	f = ft_echo_args(cmd_mtx[1]);
	if (f == 1 && i == 2)
		return (0);
	j = 1 + f;
	while (j < i - 1)
	{
		printf("%s ", cmd_mtx[j]);
		j++;
	}
	printf("%s", cmd_mtx[j]);
	if (f == 0)
		printf("\n");
	return (0);
}

int	ft_echo_args(char *arg)
{
	int	flag;

	flag = ft_strncmp(arg, "-n", 2);
	if (flag == 0 && ft_strlen(arg) == 2)
		return (1);
	return (0);
}
