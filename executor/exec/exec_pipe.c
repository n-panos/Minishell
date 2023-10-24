/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:55:52 by nacho             #+#    #+#             */
/*   Updated: 2023/10/19 10:55:52 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

int	ft_preprocess_pipe(t_mini *mini)
{
	t_pipe		*pipes;
	t_tokens	*aux_token;
	int			i;

	aux_token = mini->tk_lst;
	pipes = ft_pipe_init(mini->pipe_n);
	i = 0;
	while (aux_token)
	{
		if (aux_token->type == COMMAND)
		{
			pipes->cmd[i] = ft_init_exec(aux_token, mini->env);
			ft_in_out_pipe(pipes->cmd[i], aux_token);
			i++;
		}
		aux_token = aux_token->next;
	}
	ft_exec_pipe(pipes, mini);
	ft_free_pipes(pipes, mini->pipe_n);
	return (0);
}

void	ft_exec_pipe(t_pipe *pipes, t_mini *mini)
{
	pid_t	pidc;
	int		i;
	int		ret;

	i = 0;
	while (i <= mini->pipe_n)
	{
		pidc = -1;
		ret = ft_builtin_check(pipes->cmd[i], mini);
		if (ret == -1)
			ft_error_cmd(pipes->cmd[i]->cmd_mtx[0]);
		else if (ret == 2)
		{
			if (pipes->cmd[i]->path == NULL)
				ft_error_cmd(pipes->cmd[i]->cmd_mtx[0]);
			else
				pidc = ft_exec_solo(mini->env, pipes->cmd[i]);
		}
		if (pidc > -1)
			waitpid(pidc, NULL, 0);
		i++;
	}
}

t_pipe	*ft_pipe_init(int pipe_num)
{
	t_pipe	*pipes;
	int		i;

	i = 0;
	pipes = ft_calloc(1, sizeof(t_pipe));
	if(!pipes)
		return (NULL);
	while (i <= pipe_num)
	{
		pipes->cmd[i] = ft_calloc(1, sizeof(t_exec *));
		i++;
	}
	if (!pipes->cmd[0] || !pipes->cmd[1])
		return (NULL);
	i = 0;
	while (i < pipe_num)
	{
		pipes->fd[i] = ft_calloc(2, sizeof(int));
		if (pipe(pipes->fd[i]) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
	ft_in_out_default(pipes, pipe_num);
	return (pipes);
}

void	ft_in_out_pipe(t_exec *exec, t_tokens *token)
{
	t_tokens	*aux_token;

	aux_token = token->next;
	while (aux_token)
	{
		if (aux_token->type == PIPE || aux_token->type == COMMAND)
			break ;
		ft_in_out_type(aux_token, exec);
		aux_token = aux_token->next;
	}
}

void	ft_in_out_default(t_pipe *pipes, int pipe_num)
{
	int	i;

	pipes->cmd[0]->fd_in = 0;
	pipes->cmd[0]->fd_out = pipes->fd[0][1];
	i = 1;
	while (i < (pipe_num - 1))
	{
		pipes->cmd[i]->fd_in = pipes->fd[i - 1][0];
		pipes->cmd[i]->fd_out = pipes->fd[i][1];
		i++;
	}
	pipes->cmd[pipe_num]->fd_in = pipes->fd[i - 1][0];
	pipes->cmd[pipe_num]->fd_out = 1;
}
