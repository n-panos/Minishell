/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:16:56 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/31 09:16:56 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

int	ft_preprocess_pipe(t_mini *mini)
{
	t_pipe		*pipes;

	pipes = ft_pipe_init(mini->pipe_n, mini->cmd_n);
	ft_in_out_config(pipes, mini);
	ft_exec_pipe(pipes, mini);
	ft_free_pipes(pipes, mini->pipe_n, mini->cmd_n);
	return (0);
}

void	ft_exec_pipe(t_pipe *pipes, t_mini *mini)
{
	int		i;
	int		ret;

	i = 0;
	while (i <= mini->pipe_n)
	{
		ret = ft_builtin_check(pipes->cmd[i], mini);
		if (ret == -1)
			ft_error_cmd(pipes->cmd[i]->cmd_mtx[0]);
		else if (ret == 2)
		{
			if (pipes->cmd[i]->path == NULL)
				ft_error_cmd(pipes->cmd[i]->cmd_mtx[0]);
			else
				ft_exec_solo(mini->env, pipes->cmd[i], pipes->fd, mini->pipe_n);
		}
		i++;
	}
}

void	ft_in_out_config(t_pipe *pipes, t_mini *mini)
{
	t_tokens	*aux_token;
	int			i;

	aux_token = mini->tk_lst;
	i = 0;
	while (aux_token)
	{
		if (aux_token->type == COMMAND)
		{
			pipes->cmd[i] = ft_init_exec(aux_token, mini->env);
			i++;
		}
		aux_token = aux_token->next;
	}
	ft_in_out_default(pipes, mini->pipe_n);
	aux_token = mini->tk_lst;
	i = 0;
	while (aux_token)
	{
		if (aux_token->type == COMMAND)
		{
			ft_in_out_pipe(pipes->cmd[i], aux_token);
			i++;
		}
		aux_token = aux_token->next;
	}
}

void	ft_in_out_pipe(t_exec *exec, t_tokens *token)
{
	t_tokens	*aux_token;

	if (token->prev && token->prev->prev)
	{
		aux_token = token->prev->prev;
		if (aux_token->type == REDIRECT_INPUT || aux_token->type == HEREDOC)
			ft_in_out_type(aux_token, exec);
		else
			ft_in_out_type(token, exec);
	}
	else
		ft_in_out_type(token, exec);
}

void	ft_in_out_default(t_pipe *pipes, int pipe_num)
{
	int	i;

	pipes->cmd[0]->fd_in = 0;
	pipes->cmd[0]->fd_out = pipes->fd[0][1];
	i = 1;
	while (i < (pipe_num))
	{
		pipes->cmd[i]->fd_in = pipes->fd[i - 1][0];
		pipes->cmd[i]->fd_out = pipes->fd[i][1];
		i++;
	}
	pipes->cmd[pipe_num]->fd_in = pipes->fd[i - 1][0];
	pipes->cmd[pipe_num]->fd_out = 1;
}
