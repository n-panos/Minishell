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
	int			i;
	int			in_out;
	//int			status;
	t_exec		*odd_one;
	t_tokens	*atkn;

	i = 1;
	atkn = mini->tk_lst;
	in_out = 0;
	while (atkn && i < mini->cmd_n)
	{
		in_out = ft_exec_two(mini, atkn, in_out);
		i += 2;
		atkn = ft_return_pipe(atkn);
		atkn = ft_return_pipe(atkn);
	}
	if (i == mini->cmd_n)
	{
		odd_one = ft_init_exec(atkn, mini->env, in_out, ft_check_out(atkn));
		ft_exec_solo(mini->env, odd_one);
		ft_free_exec(odd_one);
	}
	else if (in_out > 1)
		close(in_out);
	ft_waiting(mini->cmd_n);
	//wait(&status);
	//wait(&status);
	return (0);
}

int	ft_exec_two(t_mini *mini, t_tokens *tkn, int in)
{
	t_pipes		*pipes;
	int			*fd;
	t_tokens	*atkn;
	int			out;

	atkn = tkn;
	out = 0;
	pipes = ft_config_pipe(atkn, mini->env, in);
	if (pipes->cmd2->fd_out == -1)
	{
		fd = ft_calloc(2, sizeof(int *));
		if (pipe(fd) == -1)
			exit(EXIT_FAILURE);
		pipes->cmd2->fd_out = fd[1];
		out = fd[0];
	}
	ft_pipe_exec(mini, pipes);
	return (out);
}

void	ft_pipe_exec(t_mini *mini, t_pipes *pipes)
{
	int	i;

	i = ft_builtin_check(pipes->cmd1, mini);
	if (i == 2)
	{
		if (pipes->cmd1->path == NULL)
			ft_error_cmd(pipes->cmd1->cmd_mtx[0]);
		else
			ft_exec_solo(mini->env, pipes->cmd1);
	}
	ft_free_exec(pipes->cmd1);
	i = ft_builtin_check(pipes->cmd2, mini);
	if (i == 2)
	{
		if (pipes->cmd2->path == NULL)
			ft_error_cmd(pipes->cmd2->cmd_mtx[0]);
		else
			ft_exec_solo(mini->env, pipes->cmd2);
	}
	ft_free_exec(pipes->cmd2);
	ft_free_pipes(pipes);
}

t_pipes	*ft_config_pipe(t_tokens *tkn, char **env, int in)
{
	t_pipes		*pipes;

	pipes = ft_calloc(1, sizeof(t_pipes));
	if (!pipes)
		exit(EXIT_FAILURE);
	pipes->cmd1 = ft_add_cmd(tkn, env, in);
	tkn = ft_return_pipe(tkn);
	pipes->cmd2 = ft_add_cmd(tkn, env, 0);
	if (pipes->cmd1->fd_out == -1 && pipes->cmd2->fd_in == 0)
	{
		pipes->fd = ft_calloc(2, sizeof(int *));
		if (pipe(pipes->fd) == -1)
			exit(EXIT_FAILURE);
		pipes->cmd1->fd_out = pipes->fd[1];
		pipes->cmd2->fd_in = pipes->fd[0];
	}
	return (pipes);
}

t_tokens	*ft_return_pipe(t_tokens *tkn)
{
	while (tkn)
	{
		if (tkn->type == PIPE)
		{
			if (tkn->next)
				tkn = tkn->next;
			break ;
		}
		tkn = tkn->next;
	}
	return (tkn);
}
