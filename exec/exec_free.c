/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:19:21 by nacho             #+#    #+#             */
/*   Updated: 2023/10/19 11:27:36 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

void	ft_free_pipes(t_pipe *pipes, int pipe_n)
{
	int	i;

	while (i <= pipe_n)
	{
		ft_free_exec(pipes->cmd[i]);
		i++;
	}
	i = 0;
	while (i < pipe_n)
	{
		free(pipes->fd[i][0]);
		free(pipes->fd[i][1]);
		free(pipes->fd[i]);
		i++;
	}
	free(pipes->fd);
	free(pipes);
}

void	ft_free_exec(t_exec *exec)
{
	close (exec->fd_in);
	close (exec->fd_out);
	free(exec->path);
	ft_free_mtx(exec->cmd_mtx);
	free(exec);
}
