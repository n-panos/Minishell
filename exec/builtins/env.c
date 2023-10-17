/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:20:35 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/17 13:02:21 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

int	ft_exec_env(char **env, char **cmd_mtx)
{
	int		i;
	char	**aux_mtx;

	i = 0;
	aux_mtx = ft_cpy_mtx(cmd_mtx);
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
		if (ft_strchr(aux_mtx[i], "=") != aux_mtx[i])
			printf("%s\n", aux_mtx[i]);
		i++;
	}
	ft_free_mtx(aux_mtx);
	return (0);
}

int	ft_compare(char **cmd_mtx, char *env)
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
					cmd_mtx = ft_cut_mtx(cmd_mtx, i);
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

char	**ft_cut_mtx(char **mtx, int cut)
{
	char	**ret_mtx;
	int		i;
	int		mtx_height;

	mtx_height = ft_mtx_line_cnt(mtx) - 1;
	ret_mtx = (char **)malloc(sizeof(char *) * mtx_height + 1);
	i = 0;
	while (mtx[i])
	{
		if (i != cut)
			ret_mtx[i] = ft_strdup(mtx[i]);
		i++;
	}
	ret_mtx[i - 1] = NULL;
	return (ret_mtx);
}
}

