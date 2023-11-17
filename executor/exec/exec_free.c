/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:17:24 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/17 13:28:17 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

void	ft_free_pipes(t_pipes *pipes)
{
	free(pipes->fd);
	free(pipes);
}

void	ft_free_exec(t_exec *exec)
{
	if (exec->fd_in > 1)
		close (exec->fd_in);
	if (exec->fd_out > 1)
		close (exec->fd_out);
	if (exec->path)
		free(exec->path);
	ft_mtx_free(exec->cmd_mtx);
	free(exec);
}

void	ft_close_pipe(int *fd)
{
	if (fd[0] > 1)
		close(fd[0]);
	if (fd[1] > 1)
		close(fd[1]);
	free(fd);
}
