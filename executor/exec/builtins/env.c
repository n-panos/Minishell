/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:20:35 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/09 11:24:44 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

char	**ft_env_compare(char **cmd_mtx, char *env);
int		ft_env_args(char **cmd);

int	ft_env(char **env, char **cmd_mtx)
{
	int		i;
	char	**aux_mtx;

	i = 0;
	if (ft_strlen(cmd_mtx[0]) != 3)
		return (2);
	if (ft_env_args(cmd_mtx) == 1)
		return (-1);
	aux_mtx = ft_mtx_cpy(cmd_mtx);
	while (env[i])
	{
		aux_mtx = ft_env_compare(aux_mtx, env[i]);
		i++;
	}
	i = 1;
	while (aux_mtx[i])
	{
		if (ft_strchr(aux_mtx[i], '=') != aux_mtx[i])
			printf("%s\n", aux_mtx[i]);
		i++;
	}
	ft_mtx_free(aux_mtx);
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
