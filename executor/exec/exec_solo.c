/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_solo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:56:23 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/07 11:28:25 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

int	ft_preprocess_solo(t_mini *mini)
{
	t_tokens	*aux_tkn;
	t_exec		*exec;
	int			ret;
	int			status;

	aux_tkn = mini->tk_lst;
	exec = ft_add_cmd(aux_tkn, mini, 0);
	if (exec == NULL)
		return (-1);
	ret = ft_builtin_check(exec, mini);
	if (ret == 2)
	{
		if (exec->path == NULL)
			ft_error_cmd(mini, exec->cmd_mtx[0], 0, 0);
		else if (exec->fd_in != -1 && exec->fd_out != -1)
			ft_exec_solo(mini->env, exec);
	}
	ft_free_exec(mini, exec);
	wait(&status);
	return (ret);
}

void	ft_exec_solo(char **env, t_exec *exec)
{
	pid_t	pidc;

	pidc = fork();
	if (pidc == -1)
		exit(EXIT_FAILURE);
	if (pidc == 0)
	{
		if (exec->fd_in > 0)
		{
			dup2(exec->fd_in, 0);
			close(exec->fd_in);
		}
		if (exec->fd_out > 1)
		{
			dup2(exec->fd_out, 1);
			close(exec->fd_out);
		}
		exec->ret = execve(exec->path, exec->cmd_mtx, env);
		if (exec->ret == -1)
			exit(EXIT_FAILURE);
	}
}
