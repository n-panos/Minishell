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
	int			*aux;
	t_exec		*odd;
	t_tokens	*atkn;

	i = 1;
	atkn = mini->tk_lst;
	aux = ft_calloc(2, sizeof(int *));
	aux[0] = 0;
	while (atkn && i < mini->cmd_n)
	{
		aux = ft_exec_two(mini, atkn, aux);
		if (aux == NULL)
			break ;
		i += 2;
		atkn = ft_return_pipe(atkn);
		atkn = ft_return_pipe(atkn);
	}
	if (i == mini->cmd_n)
	{
		odd = ft_add_cmd(atkn, mini, aux[0]);
		if (odd)
			ft_exec_type(mini, odd, odd->fd_in, odd->fd_out);
	}
	ft_waiting(mini, aux);
	return (0);
}

int	*ft_exec_two(t_mini *mini, t_tokens *tkn, int *in)
{
	t_pipes		*pipes;
	int			*fd;
	t_tokens	*atkn;

	atkn = tkn;
	pipes = ft_config_pipe(atkn, mini, in[0]);
	free(in);
	fd = ft_calloc(2, sizeof(int *));
	if (!pipes || !fd)
	{
		mini->status = 12;
		return (NULL);
	}
	if (ft_pipe_exec(mini, pipes, fd) == -1)
		return (NULL);
	return (fd);
}

int	ft_pipe_exec(t_mini *mini, t_pipes *pipes, int *fd)
{
	if (pipes->cmd2->fd_out == -2 && pipes->cmd2->fd_in != -1)
	{
		if (pipe(fd) == -1)
		{
			free(fd);
			return (-1);
		}
		pipes->cmd2->fd_out = fd[1];
	}
	else
	{
		fd[0] = -3;
		fd[1] = '\0';
	}
	ft_exec_type(mini, pipes->cmd1, pipes->cmd1->fd_in, pipes->cmd1->fd_out);
	ft_exec_type(mini, pipes->cmd2, pipes->cmd2->fd_in, pipes->cmd2->fd_out);
	ft_free_pipes(pipes);
	return (0);
}

t_pipes	*ft_config_pipe(t_tokens *tkn, t_mini *mini, int in)
{
	t_pipes		*pipes;

	pipes = ft_calloc(1, sizeof(t_pipes));
	if (!pipes)
		return (NULL);
	pipes->cmd1 = ft_add_cmd(tkn, mini, in);
	tkn = ft_return_pipe(tkn);
	pipes->cmd2 = ft_add_cmd(tkn, mini, 0);
	if (pipes->cmd1 == NULL || pipes->cmd2 == NULL)
		return (pipes);
	if (pipes->cmd1->fd_out == -2 && pipes->cmd2->fd_in == 0)
	{
		pipes->fd = ft_calloc(2, sizeof(int *));
		if (!pipes->fd || pipe(pipes->fd) == -1)
		{
			ft_free_exec(pipes->cmd1);
			ft_free_exec(pipes->cmd2);
			ft_free_pipes(pipes);
			return (NULL);
		}
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
