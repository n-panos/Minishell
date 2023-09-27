/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:37:50 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/09/27 13:24:20 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

char		**ft_env_delete(char **env, int erase);
static int	ft_search_igual(char *str);
char		**ft_env_rm(char **env, char *str);

char	**ft_exec_unset(char **env, char *str)
{
	char	**aux;
	int		i;
	char	**ret;

	if (str == NULL)
		return (env);
	aux = ft_split(str, ' ');
	i = 0;
	ret = env;
	while (aux[i])
	{
		if (i > 1)
			ret = ft_env_rm(env, aux[i]);
		i++;
	}
	if (i == 1)
		printf("unset: not enough arguments\n");
	return (ret);
}

char	**ft_env_delete(char **env, int erase)
{
	char	**ret;
	char	*aux;
	int		i;

	i = 0;
	aux = ft_strdup("");
	while (env[i])
	{
		if (i == erase)
			i++;
		else
		{
			aux = ft_strfjoin(aux, env[i]);
			aux = ft_strfjoin(aux, "\n");
			i++;
		}
	}
	ret = ft_split(aux, '\n');
	free(aux);
	return (ret);
}

char	**ft_env_rm(char **env, char *str)
{
	int		i;
	int		len;
	char	**ret;

	i = 0;
	while (env[i])
	{
		len = ft_search_igual(env[i]);
		if (ft_strncmp(env[i], str, len) == 0)
			ret = ft_env_delete(env, i);
		i++;
	}
	return (ret);
}

static int	ft_search_igual(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}