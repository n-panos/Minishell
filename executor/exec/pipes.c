/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:49:23 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/17 13:27:46 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

int	ft_preprocess_pipe(t_mini *mini)
{
	if (ft_is_exit(mini->tk_lst) == 1)
		return (0);
	ft_forking(mini, 0, mini->cmd_n);
	return (0);
}

void	ft_forking(t_mini *mini, int in, int n)
{
	int			fd[2];
	pid_t		pidc;
	t_tokens	*aux;
	t_exec		*exec;

	aux = mini->tk_lst;
	while (n > 0)
	{
		exec = ft_add_cmd(aux, mini, in);
		if (exec != NULL && exec->fd_in > -1)
		{
			pidc = fork();
			if (pidc == -1)
				exit(EXIT_FAILURE);
			if (pidc == 0)
				ft_child_proc(exec, fd, mini->env);
		}
		close(fd[1]);
		in = fd[0];
		aux = ft_return_pipe(aux);
		ft_free_exec(exec);
		n--;
	}
}

void	ft_child_proc(t_exec *exec, int *fd, char **env)
{
	close(fd[0]);
	dup2(exec->fd_in, 0);
	dup2(fd[1], 1);
	close(fd[1]);
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
