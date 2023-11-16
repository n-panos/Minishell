/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:17:59 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/16 16:58:11 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

int	ft_exec_type(t_mini *mini, t_exec *exec, int in, int out)
{
	int	i;

	i = 0;
	if (g_signal != 1)
	{
		i = ft_builtin_check(exec, mini);
		if (i == 2)
		{
			i = ft_is_minishell(mini, exec);
			if (exec->path == NULL)
				i = ft_error_cmd(mini, exec->cmd_mtx[0], in, out);
			else if (i == 1 && exec->fd_in != -1 && exec->fd_out != -1)
			{
				child_signal();
				ft_exec_solo(mini->env, exec);
				i = 0;
			}
		}
	}
	ft_free_exec(exec);
	return (i);
}

int	ft_is_minishell(t_mini *mini, t_exec *exec)
{
	char	str[FILENAME_MAX];
	char	*prev_shlvl;
	int		status;

	if (ft_strncmp(exec->cmd_mtx[0], "./minishell", 11) != 0  \
	|| ft_strlen(exec->cmd_mtx[0]) != 11)
		return (1);
	//ft_change_env_var(mini, "SHLVL=1");	//para debuger solo
	prev_shlvl = ft_strjoin("SHLVL", ft_get_env_var(mini->env, "SHLVL"));
	ft_change_shlvl(mini, 1);
	getcwd(str, sizeof(str));
	exec->path = ft_strjoin(str, "/minishell");
	signal_off();
	ft_exec_solo(mini->env, exec);
	wait(&status);
	mini->status = status;
	ft_change_env_var(mini, prev_shlvl);
	free(prev_shlvl);
	return (0);
}
