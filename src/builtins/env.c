/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:20:35 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/09/27 11:10:31 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

int	ft_exec_env(char **env, int flag)
{
	int	i;

	i = 0;
	if (env == NULL)
		return (1);
	while (env[i])
	{
		if (flag == 1 && ft_strncmp(env[i], "_=/", 3) == 0)
			i++;
		else
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
	return (0);
}
