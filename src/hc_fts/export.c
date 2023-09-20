/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:50:28 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/09/20 13:02:05 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

static char	ft_ascii_order(char a, char b);
static char	*ft_orden(char **env);

int	ft_exec_export(char **env)
{
	char	**aux;

	if (env == NULL)
		return (1);
	aux = ft_split(ft_orden(env), " ");
	ft_exec_env(aux);
	return (0);
}

//	NULL return = son iguales

static char	ft_ascii_order(char a, char b)
{
	if (a < b)
		return (a);
	if (a > b)
		return (b);
	if (a == b)
		return (NULL);
}

static char	*ft_orden(char **env)
{
	char	*aux;
	int		ref;
	int		i;

	if (!env)
		return (1);
	i = 0;
	ref = 0;
	ft_strncmp(env[ref], env[i], ft_strlen(env[ref]));
	return (0);
}

// test con strncmp si es positivo o negativo para ver cual va primero y luego ordenar