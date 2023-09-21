/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:50:28 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/09/21 12:59:43 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

//static char	ft_ascii_order(char a, char b);
static char	*ft_orden(char **env, int env_len, char *str_exp);

int	ft_exec_export(char **env)
{
	char	**aux;
	char	*str_exp;

	if (!env)
		return (1);
	str_exp = ft_strdup("");
	str_exp = ft_orden(env, 0, str_exp);
	printf("string que contiene exp : %s\n", str_exp);
	aux = ft_split(str_exp, ' \n');
	ft_exec_env(aux);
	free(str_exp);
	ft_free_mtx(aux);
	return (0);
}

//	NULL return = son iguales

char	ft_ascii_order(char a, char b)
{
	if (a < b)
		return (a);
	if (a > b)
		return (b);
	return ('\0');
}

int	*ft_add_used(int *prev_used, int new_used)
{
	int	*aux;
	int	i;

	i = 0;
	while (prev_used[i])
		i++;
	i++;
	aux = malloc(sizeof(int) * (i + 1));
	aux[i] = '\0';
	i--;
	aux[i] = new_used;
	while (i > 0)
	{
		i--;
		aux[i] = prev_used[i];
	}
	if (prev_used)
		free(prev_used);
	return (aux);
}

int	ft_check_list(int *list, int n)
{
	int	i;

	i = 0;
	while (list[i])
	{
		if (list[i] == n)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_orden(char **env, int j, char *str_exp)
{
	int		ref;
	int		i;
	int		*used;

	i = 1;
	ref = 0;
	while (env[j])
	{
		while (env[i])
		{
			if (ft_check_list(used, i) == 0)
			{
				if (ft_strncmp(env[ref], env[i], ft_strlen(env[ref])) < 0)
					ref = i;
			}
			i++;
		}
		str_exp = ft_strfjoin(str_exp, env[ref]);
		i = 1;
		ref = 0;
		j++;
	}
	return (str_exp);
}

// test con strncmp si es positivo o negativo para ver cual va primero y luego ordenar