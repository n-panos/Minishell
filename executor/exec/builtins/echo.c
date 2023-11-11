/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:19:04 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/11 14:18:59 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

int		ft_echo_args(char *arg);
void	ft_echo_print(int f, int i, t_exec *exec, char *dir);

int	ft_echo(t_exec *exec, char *dir)
{
	int	i;
	int	f;

	i = 0;
	if (ft_strlen(exec->cmd_mtx[0]) != 4)
		return (2);
	while (exec->cmd_mtx[i])
		i++;
	if (i == 1)
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

	flag = ft_strncmp(arg, "-n", 2);
	if (flag == 0 && ft_strlen(arg) == 2)
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
		else if (ft_strncmp(exec->cmd_mtx[j], "-n", 2) != 0)
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
