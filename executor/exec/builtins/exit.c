/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:19:23 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/12/05 18:26:38 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

int	ft_exit(t_mini *mini, t_exec *exec)
{
	int	i;

	i = 1;
	if (ft_strlen(exec->cmd_mtx[0]) != 4)
		return (2);
	while (exec->cmd_mtx[i])
		i++;
	printf("exit\n");
	mini->status = 0;
	if (i == 1)
		return (ft_free_exec(mini, exec), 1);
	if (i > 2)
	{
		ft_print_err("minishell: exit: too many arguments", NULL, NULL);
		mini->status = 1;
		return (ft_free_exec(mini, exec), 0);
	}
	if (i > 1)
		mini->status = ft_exit_more_args(exec->cmd_mtx[1]);
	return (ft_free_exec(mini, exec), 1);
}

int	ft_exit_more_args(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '\0')
	{
		ft_print_err("minishell: exit: ", arg, ": numeric argument required");
		return (255);
	}
	if (arg[0] == '-' || arg[0] == '+')
		++i;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
		{
			ft_print_err("minishell: exit: ", arg, \
			": numeric argument required");
			return (255);
		}
		++i;
	}
	i = ft_status_return(arg);
	return (i);
}

int	ft_status_return(char *arg)
{
	int	i;

	i = ft_atoi(arg);
	if (i > 255)
		i = i % 256;
	while (i < 0)
		i = i + 256;
	return (i);
}

char	*ft_get_shlvl(char **env, int flag)
{
	char	**aux;
	char	*lvl;
	int		i;

	i = 0;
	lvl = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL", 5) == 0)
		{
			aux = ft_split(env[i], '=');
			if (ft_all_isdigit(aux[1]) == 1)
			{
				i = ft_atoi(aux[1]) + flag;
				lvl = ft_itoa(i);
			}
			ft_mtx_free(aux);
			break ;
		}
		i++;
	}
	return (lvl);
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
