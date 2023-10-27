/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:33:45 by nacho             #+#    #+#             */
/*   Updated: 2023/10/25 11:38:19 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

static int	ft_more_args(char *arg, int flag);

int	ft_exit(char **cmd_mtx)
{
	int	i;

	i = 1;
	if (ft_strlen(cmd_mtx[0]) != 4)
		return (2);
	while (cmd_mtx[i])
		i++;
	printf("exit\n");
	if (i == 1)
		return (1);
	return (ft_more_args(cmd_mtx[1], i));
}

static int	ft_more_args(char *arg, int flag)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
		{
			printf("minishell: exit: %s: numeric argument required\n", arg);
			return (1);
		}
		i++;
	}
	if (flag == 2)
		return (1);
	printf("minishell: exit: too many arguments\n");
	return (0);
}