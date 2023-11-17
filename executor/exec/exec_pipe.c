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
	t_tokens	*atkn;

	i = 1;
	if (ft_is_exit(mini->tk_lst) == 1)
		return (0);
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
		ft_pipe_odd(mini, atkn, aux[0]);
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
	ft_close_pipe(in);
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
		fd[0] = -5;
		fd[1] = '\0';
	}
	ft_exec_type(mini, pipes->cmd1, pipes->cmd1->fd_in, pipes->cmd1->fd_out);
	ft_exec_type(mini, pipes->cmd2, pipes->cmd2->fd_in, pipes->cmd2->fd_out);
	ft_free_pipes(pipes);
	return (0);
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

int	ft_is_exit(t_tokens *lst)
{
	t_tokens	*tkn;

	tkn = lst;
	while (tkn)
	{
		if (tkn->type == COMMAND && ft_strncmp(tkn->value, "exit", 4) == 0 && \
		ft_strlen(tkn->value) == 4)
			return (1);
		tkn = tkn->next;
	}
	return (0);
}
