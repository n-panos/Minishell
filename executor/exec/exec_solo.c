/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_solo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:56:23 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/09 10:20:12 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

int	ft_preprocess_solo(t_mini *mini)
{
	t_tokens	*aux_tkn;
	t_exec		*exec;
	int			status;

	//	gestion ./minishell
	aux_tkn = mini->tk_lst;
	exec = ft_add_cmd(aux_tkn, mini, 0);
	if (exec == NULL)
		return (-1);
	ft_exec_type(mini, exec, 0, 0);
	wait(&status);
	return (0);
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
