/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:19:04 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/10 12:28:32 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

int		ft_echo_args(char *arg);
void	ft_echo_print(int f, int i, char **cmd_mtx, int out);

int	ft_echo(char **cmd_mtx, int out)
{
	int	i;
	int	f;

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
	ft_echo_print(f, i, cmd_mtx, out);
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

void	ft_echo_print(int f, int i, char **cmd_mtx, int out)
{
	int	j;

	j = 1 + f;
	while (j < i - 1)
	{
		if (ft_strncmp(cmd_mtx[j], "-n", 2) != 0)
		{
			ft_putstr_fd(cmd_mtx[j], out);
			ft_putchar_fd(' ', out);
		}
		j++;
	}
	ft_putstr_fd(cmd_mtx[j], out);
	if (f == 0)
		ft_putchar_fd('\n', out);
}

int	ft_check_ref(int *used, int i, int ref, char **env)
{
	if (ft_check_list(used, i) == 0)
	{
		if (ft_check_list(used, -1) == 1 && ref == 0)
			ref = i;
		else if (ft_strncmp(env[ref], env[i], ft_strlen(env[ref])) > 0)
			ref = i;
	}
	return (ref);
}
