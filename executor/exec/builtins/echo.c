/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:19:04 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/12/05 18:06:18 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

int	ft_echo(t_exec *exec, char *dir)
{
	int	i;
	int	f;

	i = 0;
	if (ft_strlen(exec->cmd_mtx[0]) != 4)
		return (2);
	while (exec->cmd_mtx[i])
		i++;
	if (i == 1 || exec->cmd_mtx[1][0] == '\0')
	{
		printf("\n");
		return (0);
	}
	f = ft_echo_args(exec->cmd_mtx[1]);
	if (f == 1 && i == 2)
		return (0);
	ft_echo_print(f, i, exec, dir);
	return (0);
}

int	ft_echo_args(char *arg)
{
	int	flag;
	int	i;

	flag = ft_strncmp(arg, "-n", 2);
	if (flag == 0)
	{
		i = 2;
		while (arg[i])
		{
			if (arg[i] != 'n')
			{
				flag = 1;
				break ;
			}
			++i;
		}
	}
	if (flag == 0)
		return (1);
	return (0);
}

void	ft_echo_print(int f, int i, t_exec *exec, char *dir)
{
	int		j;

	j = 1 + f;
	while (j < i - 1)
	{
		if (ft_strncmp(exec->cmd_mtx[j], "~", ft_strlen(exec->cmd_mtx[j])) == 0)
		{
			ft_putstr_fd(dir++, exec->fd_out);
			ft_putchar_fd(' ', exec->fd_out);
		}
		else if (ft_echo_args(exec->cmd_mtx[j]) == 0 || f == 0)
		{
			ft_putstr_fd(exec->cmd_mtx[j], exec->fd_out);
			ft_putchar_fd(' ', exec->fd_out);
		}
		j++;
	}
	if (ft_strncmp(exec->cmd_mtx[j], "~", ft_strlen(exec->cmd_mtx[j])) == 0)
		ft_putstr_fd(dir++, exec->fd_out);
	else
		ft_putstr_fd(exec->cmd_mtx[j], exec->fd_out);
	if (f == 0)
		ft_putchar_fd('\n', exec->fd_out);
}
