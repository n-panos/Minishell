/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:37:50 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/23 12:43:42 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

int	ft_unset(t_mini *mini, char **cmd_mtx)
{
	int		i;

	if (ft_strlen(cmd_mtx[0]) != 5)
		return (2);
	i = 1;
	while (cmd_mtx[i])
	{
		if (ft_strncmp(cmd_mtx[i], "PATH", 4) == 0 && \
		ft_strlen(cmd_mtx[i]) == 4)
			mini->flag_path = -1;
		ft_env_rm(mini, cmd_mtx[i]);
		i++;
	}
	return (0);
}

int	ft_env_rm(t_mini *mini, char *str)
{
	int		i;
	int		len;

	if (ft_unset_invalid(mini, str) == 0)
		return (0);
	i = 0;
	while (mini->env[i])
	{
		len = ft_search_c(mini->env[i], '=');
		if (ft_strlen(str) == (size_t)len && \
		ft_strncmp(mini->env[i], str, len) == 0)
			return (ft_env_delete(mini, i));
		i++;
	}
	return (0);
}

int	ft_env_delete(t_mini *mini, int erase)
{
	char	*aux;
	int		i;

	i = 0;
	aux = ft_strdup("");
	while (mini->env[i])
	{
		if (i != erase)
			aux = ft_join_n(aux, mini->env[i], "\n");
		++i;
	}
	ft_mtx_free(mini->env);
	mini->env = ft_split(aux, '\n');
	free(aux);
	return (0);
}

int	ft_unset_invalid(t_mini *mini, char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
	{
		mini->status = 1;
		printf("minishell: unset: `%s': not a valid identifier\n", str);
		return (0);
	}
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0)
		{
			mini->status = 1;
			printf("minishell: unset: `%s': not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}
