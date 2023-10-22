/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:20:35 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/19 13:14:40 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

static int	ft_compare(char **cmd_mtx, char *env);

int	ft_env(char **env, char **cmd_mtx)
{
	int		i;
	char	**aux_mtx;

	i = 0;
	aux_mtx = ft_mtx_cpy(cmd_mtx);
	if (ft_strlen(cmd_mtx[0]) != 3)
		return (2);
	while (env[i])
	{
		if (ft_compare(aux_mtx, env[i]) == 0)
			printf("%s\n", env[i]);
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

static int	ft_compare(char **cmd_mtx, char *env)
{
	int	i;
	int	c;

	i = 1;
	while (cmd_mtx[i])
	{
		c = 0;
		while (cmd_mtx[i][c])
		{
			if (cmd_mtx[i][c] == '=' )
			{
				if (ft_strncmp(cmd_mtx[i], env, c) == 0)
				{
					printf("%s\n", cmd_mtx[i]);
					cmd_mtx = ft_mtx_cut(cmd_mtx, i);
					return (1);
				}
			}
			else
				c++;
		}
		i++;
	}
	return (0);
}
