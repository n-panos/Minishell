/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:19:21 by nacho             #+#    #+#             */
/*   Updated: 2023/10/26 13:26:25 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

void	ft_free_pipes(t_pipe *pipes, int pipe_n)
{
	int	i;

	i = 0;
	while (i <= pipe_n)
	{
		ft_free_exec(pipes->cmd[i]);
		i++;
	}
	i = 0;
	while (i < pipe_n)
	{
		free(pipes->fd[i]);
		i++;
	}
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
