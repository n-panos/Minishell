/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:19:21 by nacho             #+#    #+#             */
/*   Updated: 2023/10/30 11:48:33 by nacho            ###   ########.fr       */
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
	ft_free_pipe_fd(pipes->fd, pipe_n);
	free(pipes);
}

void	ft_free_pipe_fd(int	**fd, int pipe_n)
{
	int	i;

	i = 0;
	ft_close_fd(fd, pipe_n, -1, -1);
	while (i < pipe_n)
	{
		free(fd[i]);
		i++;
	}
	free(fd[pipe_n]);
	free(fd);
}

int	ft_close_fd(int **fd, int pipe_n, int in, int out)
{
	int	i;
	int	ret;

	i = 0;
	ret = -1;
	while (i < pipe_n)
	{
		if (fd[i][0] != in && fd[i][1] != out)
		{
			close (fd[i][0]);
			close (fd[i][1]);
		}
		else if (fd[i][0] == in)
			ret = in;
		else if (fd[i][1] == out)
			ret = out;
		i++;
	}
	return (ret);
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
