/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:19:23 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/13 14:11:59 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

int	ft_exit(t_mini *mini, char **cmd_mtx)
{
	int	i;

	i = 1;
	if (ft_strlen(cmd_mtx[0]) != 4)
		return (2);
	while (cmd_mtx[i])
		i++;
	printf("exit\n");
	mini->status = 0;
	if (i == 1 && mini->real_shlvl == 1)
		return (1);
	if (i > 1)
		mini->status = ft_exit_more_args(cmd_mtx[1], i);
	if (mini->status == -2)
	{
		mini->status = 1;
		return (0);
	}
	if (mini->real_shlvl > 1)
	{
		ft_change_shlvl(mini, -1);
		mini->real_shlvl--;
		return (0);
	}
	return (1);
}

int	ft_exit_more_args(char *arg, int flag)
{
	int	i;

	i = 0;
	if (arg[0] == '-')
		i++;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
		{
			printf("minishell: exit: %s: numeric argument required\n", arg);
			return (255);
		}
		i++;
	}
	if (flag == 2)
	{
		i = ft_atoi(arg);
		if (i > 255)
			i = i % 256;
		while (i < 0)
			i = i + 256;
		return (i);
	}
	printf("minishell: exit: too many arguments\n");
	return (-2);
}

void	ft_change_shlvl(t_mini *mini, int flag)
{
	char	*aux;
	char	*shlvl;

	aux = ft_get_shlvl(mini->env, flag);
	if (aux == NULL)
		shlvl = ft_strdup("SHLVL=1");
	else
	{
		shlvl = ft_strjoin("SHLVL=", aux);
		free(aux);
	}
	aux = ft_add_to_env(mini->env, shlvl);
	ft_mtx_free(mini->env);
	mini->env = ft_split(aux, '\n');
	free(aux);
	free(shlvl);
}
