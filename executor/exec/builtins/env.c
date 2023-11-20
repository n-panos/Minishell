/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:20:35 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/20 15:54:34 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

int	ft_env(t_exec *exec, char **env)
{
	int		i;
	char	**aux_mtx;

	i = 0;
	if (ft_strlen(exec->cmd_mtx[0]) != 3)
		return (2);
	if (ft_env_args(exec->cmd_mtx) == 1)
		return (-1);
	if (!exec->cmd_mtx[1])
	{
		return (0);
	}
	aux_mtx = ft_mtx_cpy(exec->cmd_mtx);
	while (env[i])
	{
		aux_mtx = ft_env_compare(aux_mtx, env[i]);
		i++;
	}
	ft_env_print(aux_mtx, exec->fd_out);
	return (0);
}

int	ft_env_args(char **cmd)
{
	int		i;

	i = 1;
	while (cmd[i])
	{
		if (!ft_strchr(cmd[i], '='))
		{
			printf("env: %s: No such file or directory\n", cmd[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**ft_env_compare(char **cmd_mtx, char *env)
{
	int		i;
	int		c;

	i = 1;
	while (cmd_mtx[i])
	{
		c = 0;
		while (cmd_mtx[i][c])
		{
			if (cmd_mtx[i][c] == '=')
			{
				if (ft_strncmp(cmd_mtx[i], env, c) == 0)
				{
					printf("%s\n", cmd_mtx[i]);
					return (ft_mtx_cut(cmd_mtx, i));
				}
				break ;
			}
			c++;
		}
		i++;
	}
	if (ft_strchr(env, '='))
		printf("%s\n", env);
	return (cmd_mtx);
}

void	ft_env_print(char **mtx, int out_fd)
{
	int	i;

	i = 1;
	while (mtx[i])
	{
		if (ft_strchr(mtx[i], '=') != mtx[i])
		{
			ft_putstr_fd(mtx[i], out_fd);
			ft_putchar_fd('\n', out_fd);
		}
		i++;
	}
	ft_mtx_free(mtx);
}
