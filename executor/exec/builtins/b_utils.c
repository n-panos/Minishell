/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:49:01 by nacho             #+#    #+#             */
/*   Updated: 2023/11/21 10:56:17 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

void	ft_change_env_var(t_mini *mini, char *arg)
{
	char	*add;

	add = ft_add_to_env(mini->env, arg);
	ft_mtx_free(mini->env);
	mini->env = ft_split(add, '\n');
	free(add);
}

char	*ft_add_to_env(char **env, char *add)
{
	char	*aux;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	aux = ft_strdup("");
	while (env[i])
	{
		flag = ft_var_exists(env[i], add, flag);
		if (flag == 1)
			aux = ft_join_n(aux, add, "\n");
		else
			aux = ft_join_n(aux, env[i], "\n");
		++i;
	}
	if (flag == 0)
		aux = ft_join_n(aux, add, "\n");
	return (aux);
}

int	ft_var_exists(char *env, char *add, int flag)
{
	int	len;

	if (flag > 0)
		return (2);
	len = (ft_search_c(env, '='));
	if (len == -1)
		len = ft_strlen(env);
	if (add && ft_strncmp(env, add, len) == 0 && len == ft_search_c(add, '='))
		return (1);
	return (0);
}

int	ft_search_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
