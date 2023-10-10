/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:50:28 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/03 19:14:39 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

//AÑADIR NUEVAS VARIABLES

static int	*ft_add_used(int *prev_used, int new_used);
static int	ft_check_list(int *list, int n);
static char	*ft_orden(char **env, int env_len, char *str_exp, int *used);
static char	*ft_str_construct(int ref, char **env, char *str_exp);

int	ft_exec_export(char **env)
{
	char	**aux;
	char	*str_exp;
	int		*used;

	if (!env)
		return (1);
	used = malloc(sizeof(int *));
	if (!used)
		return (1);
	used[0] = '\0';
	str_exp = ft_strdup("");
	str_exp = ft_orden(env, 0, str_exp, used);
	aux = ft_split(str_exp, '\n');
	ft_exec_env(aux, 1);
	free(str_exp);
	ft_free_mtx(aux);
	return (0);
}

static int	*ft_add_used(int *prev_used, int new_used)
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
	if (new_used == 0)
		aux[i] = -1;
	else
		aux[i] = new_used;
	while (i > 0)
	{
		i--;
		aux[i] = prev_used[i];
	}
	free(prev_used);
	return (aux);
}

static int	ft_check_list(int *list, int n)
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

static char	*ft_str_construct(int ref, char **env, char *str_exp)
{
	char	*aux;

	aux = ft_strfjoin(str_exp, env[ref]);
	aux = ft_strfjoin(aux, "\n");
	return (aux);
}

static char	*ft_orden(char **env, int j, char *str_exp, int *used)
{
	int		ref;
	int		i;

	while (env[j])
	{
		i = 0;
		ref = 1;
		while (ft_check_list(used, ref) == 1)
			ref++;
		while (env[i])
		{
			if (ft_check_list(used, i) == 0)
			{
				if (ft_check_list(used, -1) == 1 && ref == 0)
					ref = i;
				else if (ft_strncmp(env[ref], env[i], ft_strlen(env[ref])) > 0)
					ref = i;
			}
			i++;
		}
		used = ft_add_used(used, ref);
		str_exp = ft_str_construct(ref, env, str_exp);
		j++;
	}
	return (str_exp);
}
