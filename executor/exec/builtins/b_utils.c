/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:49:01 by nacho             #+#    #+#             */
/*   Updated: 2023/11/11 13:48:58 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

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

char	*ft_join_n(char *ret, char *add, char *s_add)
{
	ret = ft_strfjoin(ret, add);
	ret = ft_strfjoin(ret, s_add);
	return (ret);
}

int	ft_var_exists(char *env, char *add, int flag)
{
	int	len;

	if (flag > 0)
		return (2);
	len = ft_search_c(env, '=');
	if (ft_strncmp(env, add, len) == 0 && len == ft_search_c(add, '='))
		return (1);
	return (0);
}

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
		if (ft_strncmp(env[i], "_=/", 3) == 0)
			break ;
		flag = ft_var_exists(env[i], add, flag);
		if (flag == 1)
			aux = ft_join_n(aux, add, "\n");
		else
			aux = ft_join_n(aux, env[i], "\n");
		i++;
	}
	if (flag == 0)
		aux = ft_join_n(aux, add, "\n");
	aux = ft_join_n(aux, env[i], "\n");
	return (aux);
}
