/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:49:23 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/21 09:17:31 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

int	ft_preprocess_pipe(t_mini *mini, int in)
{
	t_exec		*exec;
	t_tokens	*aux;
	int			fd[2];
	int			i;

	i = mini->cmd_n;
	aux = mini->tk_lst;
	while (i > 0)
	{
		exec = ft_add_cmd(aux, mini, in);
		pipe(fd);
		if (exec)
			ft_forking_pipe(mini, exec, fd, aux);
		close(fd[1]);
		in = fd[0];
		aux = ft_return_pipe(aux);
		--i;
	}
	close(in);
	ft_pipe_wait(mini);
	signal_handler(ITERATIVE);
	return (0);
}

int	ft_forking_pipe(t_mini *mini, t_exec *exec, int *fd, t_tokens *aux)
{
	pid_t		pidc;

	if (g_signal != 1)
	{
		if (ft_is_exit(aux) == 0)
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
	ft_free_exec(mini, exec);
	return (0);
}

int	ft_pipe_no_child(t_mini *mini, t_exec *exec, int *fd)
{
	int		i;

	i = 0;
	if (exec->fd_out == -2)
		exec->fd_out = fd[1];
	if (exec->fd_in <= -1 || exec->fd_out <= -1)
		return (ft_free_exec(mini, exec), 0);
	i = ft_builtin_check(exec, mini);
	if (i == 2 && exec->path == NULL)
		i = ft_error_cmd(mini, exec->cmd_mtx[0], exec->fd_in, exec->fd_out);
	if (i != 2)
		ft_free_exec(mini, exec);
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
