/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_solo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:56:23 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/16 16:53:24 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

int	ft_preprocess_solo(t_mini *mini)
{
	t_tokens	*aux_tkn;
	t_exec		*exec;
	int			status;
	int			ret;

	aux_tkn = mini->tk_lst;
	exec = ft_add_cmd(aux_tkn, mini, 0);
	if (exec == NULL)
		return (-1);
	ret = ft_exec_type(mini, exec, 0, 0);
	wait(&status);
	signal_handler(ITERATIVE);
	return (ret);
}

void	ft_exec_solo(char **env, t_exec *exec)
{
	pid_t	pidc;

	pidc = fork();
	if (pidc == -1)
	{
		printf("minishell: error while forking process\n");
		exit(EXIT_FAILURE);
	}
	if (pidc == 0)
		ft_child_process(env, exec);
}

void	ft_child_process(char **env, t_exec *exec)
{
	int		*fd;

	fd = NULL;
	if (exec->fd_in == -5)
	{
		exec->fd_in = ft_closed_pipe(fd);
	}
	if (exec->fd_in > 0)
	{
		dup2(exec->fd_in, 0);
		close(exec->fd_in);
	}
	if (fd)
		free(fd);
	if (exec->fd_out > 1)
	{
		dup2(exec->fd_out, 1);
		close(exec->fd_out);
	}
	execve(exec->path, exec->cmd_mtx, env);
	printf("minishell: executing error\n");
	exit(EXIT_FAILURE);
}
