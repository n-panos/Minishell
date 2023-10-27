/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:19:21 by nacho             #+#    #+#             */
/*   Updated: 2023/10/27 12:41:04 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

void	ft_free_pipes(t_pipe *pipes, int pipe_n, int cmd_n)
{
	int	i;

	i = 0;
	while (i < cmd_n)
	{
		ft_free_exec(pipes->cmd[i]);
		i++;
	}
	free(pipes->cmd[cmd_n]);
	free(pipes->cmd);
	i = 0;
	while (i < pipe_n)
	{
		free(pipes->fd[i]);
		i++;
	}
	free(pipes->fd[pipe_n]);
	free(pipes->fd);
	free(pipes);
}

void	ft_free_exec(t_exec *exec)
{
	if (exec->fd_in > 0)
		close (exec->fd_in);
	if (exec->fd_out > 1)
		close (exec->fd_out);
	free(exec->path);
	ft_mtx_free(exec->cmd_mtx);
	free(exec);
}
