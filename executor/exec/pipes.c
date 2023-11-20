/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:49:23 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/20 10:06:35 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

int	ft_preprocess_pipe(t_mini *mini)
{
	ft_forking_pipe(mini, 0, mini->cmd_n);
	ft_pipe_wait(mini);
	signal_handler(ITERATIVE);
	return (0);
}

int	ft_forking_pipe(t_mini *mini, int in, int n)
{
	int			fd[2];
	pid_t		pidc;
	t_tokens	*aux;
	t_exec		*exec;

	aux = mini->tk_lst;
	while (n > 0)
	{
		exec = ft_add_cmd(aux, mini, in);
		pipe(fd);
		if (ft_is_exit(aux) == 0)
		{
			if (g_signal != 1)
			{
				if (ft_pipe_no_child(mini, exec, fd) != 2)
					return (0);
				pidc = fork();
				child_signal();
				if (pidc == -1 || !exec)
					exit(EXIT_FAILURE);
				if (pidc == 0)
					ft_executing_pipe_cmds(exec, fd, mini->env);
			}
		}
		close(fd[1]);
		in = fd[0];
		aux = ft_return_pipe(aux);
		ft_free_exec(exec);
		n--;
	}
	close(in);
	return (0);
}

int	ft_pipe_no_child(t_mini *mini, t_exec *exec, int *fd)
{
	int	i;

	i = 0;
	if (exec->fd_out == -2)
		exec->fd_out = fd[1];
	i = ft_builtin_check(exec, mini);
	if (i == 2)
	{
		if (exec->path == NULL || exec->fd_in == -1 || exec->fd_out == -1)
			i = ft_error_cmd(mini, exec->cmd_mtx[0], exec->fd_in, exec->fd_out);
	}
	if (i != 2)
		ft_free_exec(exec);
	return (i);
}

void	ft_executing_pipe_cmds(t_exec *exec, int *fd, char **env)
{
	close(fd[0]);
	dup2(exec->fd_in, 0);
	dup2(exec->fd_out, 1);
	close(fd[1]);
	execve(exec->path, exec->cmd_mtx, env);
	printf("minishell: executing error\n");
}
