/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:49:23 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/18 10:52:42 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

int	ft_preprocess_pipe_a(t_mini *mini)
{
	if (ft_is_exit(mini->tk_lst) == 1)
		return (0);
	ft_forking(mini, 0, mini->cmd_n);
	ft_waiting(mini);
	return (0);
}

int	ft_forking_a(t_mini *mini, int in, int n)
{
	int			fd[2];
	pid_t		pidc;
	t_tokens	*aux;
	t_exec		*exec;

	aux = mini->tk_lst;
	while (n > 0)
	{
		exec = ft_add_cmd(aux, mini, in);
		if (!pipe(fd) || exec == NULL)
			return (-1);
		pidc = fork();
		if (pidc == -1)
			exit(EXIT_FAILURE);
		if (pidc == 0)
			ft_child_proc(mini, exec, fd);
		close(fd[1]);
		in = fd[0];
		aux = ft_return_pipe(aux);
		ft_free_exec(exec);
		n--;
	}
	return (0);
}

int	ft_child_proc_a(t_mini *mini, t_exec *exec, int *fd)
{
	int	i;

	i = 0;
	if (g_signal != 1)
	{
		i = ft_builtin_check(exec, mini);
		if (i == 2)
		{
			i = ft_is_minishell(mini, exec);
			if (exec->path == NULL)
				i = ft_error_cmd(mini, exec->cmd_mtx[0], exec->fd_in, exec->fd_out);
			else if (i == 1 && exec->fd_in != -1 && exec->fd_out != -1)
			{
				child_signal();
				ft_executing_cmds(exec, fd, mini->env);
				i = 0;
			}
		}
	}
	ft_free_exec(exec);
	return (i);
}


void	ft_executing_cmds_a(t_exec *exec, int *fd, char **env)
{
	close(fd[0]);
	dup2(exec->fd_in, 0);
	dup2(exec->fd_out, 1);
	close(exec->fd_out);
	execve(exec->path, exec->cmd_mtx, env);
	printf("minishell: executing error\n");
	exit(EXIT_FAILURE);
}

int	ft_is_exit(t_tokens *lst)
{
	t_tokens	*tkn;

	tkn = lst;
	while (tkn)
	{
		if (tkn->type == COMMAND && ft_strncmp(tkn->value, "exit", 4) == 0 && \
		ft_strlen(tkn->value) == 4)
			return (1);
		if (tkn->type == COMMAND && ft_strncmp(tkn->value, "bash", 4) == 0 && \
		ft_strlen(tkn->value) == 4)
			return (1);
		if (tkn->type == COMMAND && ft_strncmp(tkn->value, "./minishell", 11) \
		== 0 && ft_strlen(tkn->value) == 11)
			return (1);
		tkn = tkn->next;
	}
	return (0);
}
