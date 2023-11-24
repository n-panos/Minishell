/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:05:17 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/24 13:05:10 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

char	*ft_increment_shlvl(char **env)
{
	char	*shlvl;
	char	*new_shlvl;
	int		i;
	int		shlvl_int;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "SHLVL=", 6) != 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	shlvl = ft_substr(env[i], 6, ft_strlen(env[i]) - 6);
	if (shlvl == NULL)
		return (NULL);
	shlvl_int = ft_atoi(shlvl);
	free(shlvl);
	shlvl_int++;
	new_shlvl = ft_itoa(shlvl_int);
	if (new_shlvl == NULL)
		return (NULL);
	free(env[i]);
	env[i] = ft_strjoin("SHLVL=", new_shlvl);
	free(new_shlvl);
	return (env[i]);
}
