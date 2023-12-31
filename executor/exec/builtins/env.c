/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:20:35 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/12/16 10:34:00 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

int	ft_env(t_mini *mini, t_exec *exec)
{
	int		i;
	char	**aux_mtx;

	i = 0;
	if (ft_strlen(exec->cmd_mtx[0]) != 3)
		return (2);
	if (ft_env_args(exec, mini) == 1)
		return (127);
	aux_mtx = ft_mtx_cpy(exec->cmd_mtx);
	while (mini->env[i])
	{
		aux_mtx = ft_env_compare(aux_mtx, mini->env[i], exec->fd_out);
		i++;
	}
	i = 1;
	while (aux_mtx[i])
	{
		if (ft_strchr(aux_mtx[i], '=') != aux_mtx[i])
			ft_env_print(aux_mtx[i], exec->fd_out);
		i++;
	}
	ft_mtx_free(aux_mtx);
	return (0);
}

int	ft_env_args(t_exec *exec, t_mini *mini)
{
	int		i;
	char	*aux;

	i = 1;
	if (!exec->path)
		return (ft_print_err("minishell: env: command not found", NULL, \
		NULL), 1);
	if (mini->flag_path == -1)
		return (ft_print_err("minishell: env: No such file or directory", \
		NULL, NULL), 1);
	while (exec->cmd_mtx[i])
	{
		if (!ft_strchr(exec->cmd_mtx[i], '='))
		{
			ft_print_err("env: ", exec->cmd_mtx[i],
				": No such file or directory");
			return (1);
		}
		i++;
	}
	aux = ft_strjoin("_=", exec->path);
	ft_change_env_var(mini, aux, 0);
	free(aux);
	return (0);
}

char	**ft_env_compare(char **cmd_mtx, char *env, int out_fd)
{
	int		i;
	int		c;

	i = 1;
	while (cmd_mtx[i])
	{
		c = ft_search_c(cmd_mtx[i], '=');
		if (c >= 0)
		{
			if (ft_strncmp(cmd_mtx[i], env, c) == 0)
			{
				ft_env_print(cmd_mtx[i], out_fd);
				return (ft_mtx_cut(cmd_mtx, i));
			}
			break ;
		}
		i++;
	}
	if (ft_strchr(env, '='))
		ft_env_print(env, out_fd);
	return (cmd_mtx);
}

void	ft_env_print(char *str, int out_fd)
{
	ft_putstr_fd(str, out_fd);
	ft_putchar_fd('\n', out_fd);
}
