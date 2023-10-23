/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:11:50 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/23 13:31:34 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

// return es -1 si hubo algun error de ejecucion, 0 si ejecuto bien, 
// 1 si viene del comando exit y hay que cerrar la consola

int	ft_execute(t_mini *mini)
{
	int			ret;
	t_tokens	*a_tkn;

	ret = 0;
	//if (mini->cmd_n == 0)
		//ret = ft_no_cmd(mini);
	if (mini->cmd_n == 1)
		ret = ft_preprocess_solo(mini);
	else if (mini->cmd_n > 1)
		ret = ft_preprocess_pipe(mini);
	return (ret);
}

// return 2 si no ha hecho nada, return 0 sin problema, 
// 1 es exit, -1 error

int	ft_builtin_check(t_exec *exec, t_mini *mini)
{
	int	i;

	i = 2;
	if (ft_strncmp(exec->cmd_mtx[0], "cd", 2) == 0)
		i = ft_cd(exec->cmd_mtx);
	else if (ft_strncmp(exec->cmd_mtx[0], "echo", 4) == 0)
		i = ft_echo(exec->cmd_mtx);
	else if (ft_strncmp(exec->cmd_mtx[0], "env", 3) == 0)
		i = ft_env(mini->env, exec->cmd_mtx);
	else if (ft_strncmp(exec->cmd_mtx[0], "exit", 4) == 0)
		i = ft_exit(exec->cmd_mtx);
	// else if (ft_strncmp(exec->cmd_mtx[0], "export", 6))
	// 	i = ft_export(mini, exec->cmd_mtx);
	else if (ft_strncmp(exec->cmd_mtx[0], "pwd", 3) == 0)
		i = ft_pwd(exec->cmd_mtx);
	else if (ft_strncmp(exec->cmd_mtx[0], "unset", 5) == 0)
		i = ft_unset(mini, exec->cmd_mtx);
	return (i);
}
