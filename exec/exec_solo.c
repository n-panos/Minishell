/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_solo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:56:23 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/31 13:00:15 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

int	ft_preprocess_solo(t_mini *mini)
{
	t_tokens	*aux_tkn;
	t_exec		*exec;
	int			ret;
	int			status;

	aux_tkn = mini->tk_lst;
	while (aux_tkn)
	{
		if (aux_tkn->type == COMMAND)
			break ;
		aux_tkn = aux_tkn->next;
	}
	exec = ft_init_exec(aux_tkn, mini->env, 0, 1);
	ft_in_out_type(mini->tk_lst, exec);
	if (exec == NULL)
		return (-1);
	ret = ft_builtin_check(exec, mini);
	if (ret == 2)
	{
		if (exec->path == NULL)
			ft_error_cmd(exec->cmd_mtx[0]);
		else
			ft_exec_solo(mini->env, exec);
	}
	ft_free_exec(exec);
	wait(&status);
	return (ret);
}

pid_t	ft_exec_solo(char **env, t_exec *exec)
{
	pid_t	pidc;

	pidc = fork();
	if (pidc == -1)
		exit(EXIT_FAILURE);
	if (pidc == 0)
	{
		if (exec->fd_in > 0)
		{
			dup2(exec->fd_in, 0);
			close(exec->fd_in);
		}
		if (exec->fd_out > 1)
		{
			dup2(exec->fd_out, 1);
			close(exec->fd_out);
		}
		if (execve(exec->path, exec->cmd_mtx, env) == -1)
			exit(EXIT_FAILURE);
	}
	return (pidc);
}

void	ft_in_out_type(t_tokens *token, t_exec *exec)
{
	t_tokens	*a_tkn;

	a_tkn = token;
	while (a_tkn)
	{
		if (a_tkn->type == PIPE)
			break ;
		if (exec->fd_in > 0 && (a_tkn->type == HEREDOC \
		|| a_tkn->type == REDIRECT_INPUT))
			close(exec->fd_in);
		if (a_tkn->type == HEREDOC)
			exec->fd_in = here_doc(a_tkn->next->value);
		else if (a_tkn->type == REDIRECT_INPUT)
			exec->fd_in = open(a_tkn->next->value, O_RDONLY);
		if (exec->fd_out > 1 && (a_tkn->type == REDIRECT_OUTPUT \
		|| a_tkn->type == REDIRECT_APPEND))
			close (exec->fd_out);
		if (a_tkn->type == REDIRECT_OUTPUT)
			exec->fd_out = open(a_tkn->next->value, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (a_tkn->type == REDIRECT_APPEND)
			exec->fd_out = open(a_tkn->next->value, \
			O_WRONLY | O_APPEND, 0644);
		a_tkn = a_tkn->next;
	}
}
