/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:49:01 by nacho             #+#    #+#             */
/*   Updated: 2023/12/16 12:14:52 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

void	ft_change_env_var(t_mini *mini, char *arg, int flag)
{
	char	*add;

	if (mini->env[0])
	{
		if (flag == 1 && mini->env[1])
			ft_env_rm(mini, "_");
		add = ft_add_to_env(mini->env, arg);
		ft_mtx_free(mini->env);
		mini->env = ft_split(add, '\n');
		free(add);
	}
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
	int	len_env;
	int	len_add;

	if (flag > 0)
		return (2);
	len_env = (ft_search_c(env, '='));
	len_add = ft_search_c(add, '=');
	if (add && ft_strncmp(env, add, len_env) == 0 && \
	len_env != -1 && len_add == -1)
		return (2);
	if (len_env == -1)
		len_env = ft_strlen(env);
	if (len_add == -1)
		len_add = ft_strlen(add);
	if (add && ft_strncmp(env, add, len_env) == 0 && len_env == len_add)
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

char	*ft_get_env_var(char **env, char *str)
{
	char	*dir;
	int		i;
	int		len;

	i = 0;
	dir = NULL;
	len = ft_strlen(str);
	while (env[i])
	{
		if (ft_strncmp(env[i], str, len) == 0)
		{
			dir = ft_strchr(env[i], '=');
			if (ft_strlen(env[i]) <= (size_t)len + 1)
				return (dir);
			break ;
		}
		i++;
	}
	return (dir);
}
