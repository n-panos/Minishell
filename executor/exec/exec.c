/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:11:50 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/22 12:33:21 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

int	ft_execute(t_mini *mini)
{
	int	ret;

	ret = 0;
	if (mini->pipe_n == 0)
		ret = ft_preprocess_solo(mini);
	else if (mini->pipe_n > 0)
		ret = ft_preprocess_pipe(mini);
	return (ret);
}

// return 2 si no ha hecho nada, return 0 sin problema, 
// 1 es exit, -1 error

int	ft_builtin_check(t_exec *exec, t_mini *mini)
{
	int	i;

	i = 2;
	if (ft_strncmp(exec->cmd_mtx[0], "cd", 2))
		i = ft_cd(exec->cmd_mtx);
	else if (ft_strncmp(exec->cmd_mtx[0], "echo", 4))
		i = ft_echo(exec->cmd_mtx);
	else if (ft_strncmp(exec->cmd_mtx[0], "env", 3))
		i = ft_env(mini->env, exec->cmd_mtx);
	else if (ft_strncmp(exec->cmd_mtx[0], "exit", 4))
		i = ft_exit(exec->cmd_mtx);
	// else if (ft_strncmp(exec->cmd_mtx[0], "export", 6))
	// 	i = ft_export(mini, exec->cmd_mtx);
	else if (ft_strncmp(exec->cmd_mtx[0], "pwd", 3))
		i = ft_pwd(exec->cmd_mtx);
	else if (ft_strncmp(exec->cmd_mtx[0], "unset", 5))
		i = ft_unset(mini, exec->cmd_mtx);
	return (i);
}
