/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:19:43 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/29 12:38:55 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

int	ft_pwd(t_exec *exec, char **env)
{
	char	str[FILENAME_MAX];
	char	*aux;

	if (ft_strlen(exec->cmd_mtx[0]) != 3)
		return (2);
	if (exec->cmd_mtx[1] && exec->cmd_mtx[1][0] == '-' && \
	exec->cmd_mtx[1][1] != '\0' && exec->cmd_mtx[1][1] != '-')
	{
		printf("minishell: pwd: -%c", exec->cmd_mtx[1][1]);
		printf(": invalid option\npwd: usage: pwd [-LP]\n");
	}
	if (getcwd(str, sizeof(str)) != NULL)
	{
		ft_putstr_fd(str, exec->fd_out);
		ft_putchar_fd('\n', exec->fd_out);
	}
	else
	{
		aux = ft_get_env_var(env, "PWD");
		ft_putstr_fd(++aux, exec->fd_out);
		ft_putchar_fd('\n', exec->fd_out);
	}
	return (0);
}
