/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:35:34 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/12/05 18:54:36 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

char	*ft_orden(char **env, int j, char *str_exp, int *used)
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
			ref = ft_check_ref(used, i, ref, env);
			i++;
		}
		used = ft_add_used(used, ref);
		str_exp = ft_str_construct(ref, env, str_exp);
		j++;
	}
	free(used);
	return (str_exp);
}

char	*ft_str_construct(int ref, char **env, char *str_exp)
{
	char	*aux;
	char	**comillas;

	if (ft_strncmp(env[ref], "_=/", 3) == 0)
		return (str_exp);
	comillas = ft_split(env[ref], '=');
	aux = ft_strfjoin(str_exp, "declare -x ");
	aux = ft_strfjoin(aux, comillas[0]);
	if (comillas[1])
	{
		aux = ft_strfjoin(aux, "='");
		aux = ft_join_n(aux, comillas[1], "'\n");
	}
	else if (ft_search_c(env[ref], '=') != -1)
		aux = ft_join_n(aux, "='", "'\n");
	else
		aux = ft_strfjoin(aux, "\n");
	ft_mtx_free(comillas);
	return (aux);
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

int	ft_check_ref(int *used, int i, int ref, char **env)
{
	if (ft_check_list(used, i) == 0)
	{
		if (ft_check_list(used, -1) == 1 && ref == 0)
			ref = i;
		else if (ft_strncmp(env[ref], env[i], ft_strlen(env[ref])) > 0)
			ref = i;
	}
	return (ref);
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
